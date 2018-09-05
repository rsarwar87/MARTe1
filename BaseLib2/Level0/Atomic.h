/*
 * Copyright 2011 EFDA | European Fusion Development Agreement
 *
 * Licensed under the EUPL, Version 1.1 or – as soon they 
   will be approved by the European Commission - subsequent  
   versions of the EUPL (the "Licence"); 
 * You may not use this work except in compliance with the 
   Licence. 
 * You may obtain a copy of the Licence at: 
 *  
 * http://ec.europa.eu/idabc/eupl
 *
 * Unless required by applicable law or agreed to in 
   writing, software distributed under the Licence is 
   distributed on an "AS IS" basis, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either 
   express or implied. 
 * See the Licence for the specific language governing 
   permissions and limitations under the Licence. 
 *
 * $Id: Atomic.h 75 2012-11-07 09:42:41Z aneto $
 *
**/

/**
 * @file
 * Routines that are performed by the CPU without interruption.
 * These ones are slower than those in SPAtomic.h, but are granted
 * to work on multiprocessor machines.
 */
#ifndef ATOMIC_H
#define ATOMIC_H

#include "GenDefs.h"
#include "Sleep.h"

#if defined(_LINUX) && defined(_ARM) 
//Maybe put in other .h .c
extern "C"{

        #define atomic_inc_and_test(v)  (pa_atomic_add(v,1) == 0)



	typedef   int  pa_atomic_t;

	#define PA_ATOMIC_INIT(v) { .value = (v) }

	static inline void pa_memory_barrier(void) {
	#ifdef ATOMIC_ARM_MEMORY_BARRIER_ENABLED
	    asm volatile ("mcr	p15, 0, r0, c7, c10, 5	@ dmb");
	#endif

	}

	static inline int pa_atomic_load(const pa_atomic_t *a) {
	    pa_memory_barrier();
	    return *a;
	}

	static inline void pa_atomic_store(pa_atomic_t *a, int i) {
	    *a = i;
	    pa_memory_barrier();
	}

	// Returns the previously set value 
	static inline int pa_atomic_add(pa_atomic_t *a, int i) {
	    unsigned long not_exclusive;
	    int new_val, old_val;

	    pa_memory_barrier();
	    do {
		asm volatile ("ldrex	%0, [%3]\n"
			      "add 	%2, %0, %4\n"
			      "strex	%1, %2, [%3]\n"
			      : "=&r" (old_val), "=&r" (not_exclusive), "=&r" (new_val)
			      : "r" (a), "Ir" (i)
			      : "cc");
	    } while(not_exclusive);
	    pa_memory_barrier();

	    return old_val;
	}

	// Returns the previously set value 
	static inline int pa_atomic_sub(pa_atomic_t *a, int i) {
	    unsigned long not_exclusive;
	    int new_val, old_val;

	    pa_memory_barrier();
	    do {
		asm volatile ("ldrex	%0, [%3]\n"
			      "sub 	%2, %0, %4\n"
			      "strex	%1, %2, [%3]\n"
			      : "=&r" (old_val), "=&r" (not_exclusive), "=&r" (new_val)
			      : "r" (a), "Ir" (i)
			      : "cc");
	    } while(not_exclusive);
	    pa_memory_barrier();

	    return old_val;
	}

	static inline int pa_atomic_inc(pa_atomic_t *a) {
	    return pa_atomic_add(a, 1);
	}

	static inline int pa_atomic_dec(pa_atomic_t *a) {
	    return pa_atomic_sub(a, 1);
	}

	static inline int pa_atomic_cmpxchg(pa_atomic_t *a, int old_i, int new_i) {
	    unsigned long not_equal, not_exclusive;

	    pa_memory_barrier();
	    do {
		asm volatile ("ldrex	%0, [%2]\n"
			      "subs	%0, %0, %3\n"
			      "mov	%1, %0\n"
			      "strexeq %0, %4, [%2]\n"
			      : "=&r" (not_exclusive), "=&r" (not_equal)
			      : "r" (a), "Ir" (old_i), "r" (new_i)
			      : "cc");
	    } while(not_exclusive && !not_equal);
	    pa_memory_barrier();

	    return !not_equal;
	}

	typedef struct pa_atomic_ptr {
	    volatile unsigned long value;
	} pa_atomic_ptr_t;

	#define PA_ATOMIC_PTR_INIT(v) { .value = (long) (v) }

	static inline void* pa_atomic_ptr_load(const pa_atomic_ptr_t *a) {
	    pa_memory_barrier();
	    return (void*) a->value;
	}

	static inline void pa_atomic_ptr_store(pa_atomic_ptr_t *a, void *p) {
	    a->value = (unsigned long) p;
	    pa_memory_barrier();
	}

	static inline int pa_atomic_ptr_cmpxchg(pa_atomic_ptr_t *a, void *old_p, void* new_p) {
	    unsigned long not_equal, not_exclusive;

	    pa_memory_barrier();
	    do {
		asm volatile ("ldrex	%0, [%2]\n"
			      "subs	%0, %0, %3\n"
			      "mov	%1, %0\n"
			      "strexeq %0, %4, [%2]\n"
			      : "=&r" (not_exclusive), "=&r" (not_equal)
			      : "r" (&a->value), "Ir" (old_p), "r" (new_p)
			      : "cc");
	    } while(not_exclusive && !not_equal);
	    pa_memory_barrier();

	    return !not_equal;
	}

}
#endif
/** A collector of functions that are executed atomically even on multiprocessor machines. */
class Atomic{

#if defined _SOLARIS
// Temporary solution until atomic full implementation on Solaris
private:

    /** The state of a semaphore. */
    static int32 privateSem;

    /** Lock function implemented with a semaphore. */
    static inline bool PrivateLock(){
        while(!Atomic::TestAndSet((int32 *)&privateSem)){
            SleepMsec(1);
        }
        return True;
    }

    /** Unlock function implemented with a semaphore. */
    static inline bool PrivateUnLock(){
        privateSem = 0;
        return True;
    }
#endif

public:
    /** Atomically increment a 32 bit integer in memory. */
    static inline void Increment (volatile int32 *p ){
#if defined(_CINT)
#elif defined(_MSC_VER)
        __asm  {
            mov   ebx,p
            lock inc DWORD PTR[ebx]
        }
#elif defined(_VX5100) || defined(_VX5500)|| defined(_V6X5100)|| defined(_V6X5500)

        volatile register int32 MSR,temp;
        asm volatile(
            "mfmsr %0\n"                // Gets the MSR
            "rlwinm %1,%0,0,17,15\n"    // Reset the EE flag to disable the interrupts
            "mtmsr %1\n"                // Update the MSR
            "lwzx %1,0,%2\n"            // Store *p in a register, otherwise it doesn't work
            "addi %1,%1,1\n"            // Increment
            "stwx %1,0,%2\n"            // Store the result in *p
            "mtmsr %0"                  // Update the MSR
            :"=r" (MSR),"=r"(temp), "=r" (p) : "0" (MSR),"1"(temp), "2" (p)
        );

#elif defined(_VX68K)
        asm volatile(
            "ADDQL #1,(%0)\n"
            : : "d" (p)
        );
#elif defined(_LINUX) && defined(_ARM) 
	
	pa_atomic_inc((pa_atomic_t *)p);

#elif (defined(_RTAI) || defined(_LINUX) || defined(_MACOSX))
        asm volatile(
            "lock incl (%0)\n"
            : : "r" (p)
            );
#elif defined(_SOLARIS)
// This is not appropriate .... but works for the moment...
    Atomic::PrivateLock();
    *p = *p + 1;
    Atomic::PrivateUnLock();
#else
#endif
    }

    /** Atomically increment a 16 bit integer in memory. */
    static inline void Increment (volatile int16 *p){
#if defined(_CINT)
#elif defined(_MSC_VER)
        __asm  {
            mov   ebx,p
            lock inc WORD PTR[ebx]
        }
#elif defined(_VX5100) || defined(_VX5500)|| defined(_V6X5100)|| defined(_V6X5500)

        volatile register int32 MSR, temp;
        asm volatile(
            "mfmsr %0\n"                // Gets the MSR
            "rlwinm %1,%0,0,17,15\n"    // Reset the EE flag to disable the interrupts
            "mtmsr %1\n"                // Update the MSR
            "lhzx %1,0,%2\n"            // Store *p in a register, otherwise it doesn't work
            "addi  %1,%1,1\n"           // Increment
            "sthx %1,0,%2\n"            // Store the result in *p
            "mtmsr %0"                  // Update the MSR
            :"=r" (MSR),"=r"(temp), "=r" (p) : "0" (MSR),"1"(temp), "2" (p)

        );
#elif defined(_VX68K)
        asm volatile(
            "ADDQW #1,(%0)\n"
            : : "d" (p)
        );
#elif defined(_LINUX) && defined(_ARM) 
	printf("Increment (volatile int16 *p) NOT YET IMPLEMENTED for ARM1176 rpi\n");
#elif (defined(_RTAI) || defined(_LINUX) || defined(_MACOSX))
        asm volatile(
            "lock incw (%0)\n"
            : : "r" (p)
            );
#elif defined(_SOLARIS)
// This is not appropriate .... but works for the moment...
    Atomic::PrivateLock();
    *p = *p + 1;
    Atomic::PrivateUnLock();
#else
#endif
    }

    /** Atomically increment a 8 bit integer in memory. */
    static inline void Increment (volatile int8 *p){
#if defined(_CINT)
#elif defined(_MSC_VER)
        __asm  {
            mov   ebx,p
            lock inc [ebx]
        }
#elif defined(_VX5100) || defined(_VX5500)|| defined(_V6X5100)|| defined(_V6X5500)

        volatile register int32 MSR, temp;
        asm volatile(
            "mfmsr %0\n"                // Gets the MSR
            "rlwinm %1,%0,0,17,15\n"    // Reset the EE flag to disable the interrupts
            "mtmsr %1\n"                // Update the MSR
            "lbzx %1,0,%2\n"            // Store *p in a register, otherwise it doesn't work
            "addi  %1,%1,1\n"           // Increment
            "stbx %1,0,%2\n"            // Store the result in *p
            "mtmsr %0"                  // Update the MSR
            :"=r" (MSR),"=r"(temp), "=r" (p) : "0" (MSR),"1"(temp), "2" (p)
        );
#elif defined(_VX68K)
        asm volatile(
            "ADDQB #1,(%0)\n"
            : : "d" (p)
        );
#elif defined(_LINUX) && defined(_ARM) 
	printf("Increment (volatile int8 *p) NOT YET IMPLEMENTED for ARM1176 rpi\n");

#elif (defined(_RTAI) || defined(_LINUX) || defined(_MACOSX))
        asm volatile(
            "lock incb (%0)\n"
            : : "r" (p)
            );
#elif defined(_SOLARIS)
// This is not appropriate .... but works for the moment...
    Atomic::PrivateLock();
    *p = *p + 1;
    Atomic::PrivateUnLock();
#else
#endif
    }

    /** Atomically decrement a 32 bit integer in memory. */
    static inline void Decrement (volatile int32 *p){
#if defined(_CINT)
#elif defined(_MSC_VER)
        __asm  {
            mov   ebx,p
            lock dec DWORD PTR[ebx]
        }
#elif defined(_VX5100) || defined(_VX5500)|| defined(_V6X5100)|| defined(_V6X5500)

        volatile register int32 MSR, temp;
        asm volatile(
            "mfmsr %0\n"                // Gets the MSR
            "rlwinm %1,%0,0,17,15\n"    // Reset the EE flag to disable the interrupts
            "mtmsr %1\n"                // Update the MSR
            "lwzx %1,0,%2\n"            // Store *p in a register, otherwise it doesn't work
            "subi  %1,%1,1\n"           // Increment
            "stwx %1,0,%2\n"            // Store the result in *p
            "mtmsr %0"                  // Update the MSR
            :"=r" (MSR),"=r"(temp), "=r" (p) : "0" (MSR),"1"(temp), "2" (p)
        );
#elif defined(_VX68K)
        asm volatile(
            "SUBQL #1,(%0)\n"
            : : "d" (p)
        );
#elif defined(_LINUX) && defined(_ARM) 
	
	pa_atomic_dec((pa_atomic_t *)p);
#elif (defined(_RTAI) || defined(_LINUX) || defined(_MACOSX))
        asm volatile(
            "lock decl (%0)\n"
            : : "r" (p)
            );
#elif defined(_SOLARIS)
// This is not appropriate .... but works for the moment...
    Atomic::PrivateLock();
    *p = *p - 1;
    Atomic::PrivateUnLock();
#else
#endif
    }

    /** Atomically decrement a 16 bit integer in memory. */
    static inline void Decrement (volatile int16 *p){
#if defined(_CINT)
#elif defined(_MSC_VER)
        __asm  {
            mov   ebx,p
            lock dec WORD PTR[ebx]
        }
#elif defined(_VX5100) || defined(_VX5500)|| defined(_V6X5100)|| defined(_V6X5500)

        volatile register int32 MSR, temp;
        asm volatile(
            "mfmsr %0\n"                // Gets the MSR
            "rlwinm %1,%0,0,17,15\n"    // Reset the EE flag to disable the interrupts
            "mtmsr %1\n"                // Update the MSR
            "lhzx %1,0,%2\n"            // Store *p in a register, otherwise it doesn't work
            "subi  %1,%1,1\n"           // Increment
            "sthx %1,0,%2\n"            // Store the result in *p
            "mtmsr %0"                  // Update the MSR
            :"=r" (MSR),"=r"(temp), "=r" (p) : "0" (MSR),"1"(temp), "2" (p)
        );
#elif defined(_VX68K)
        asm volatile(
            "SUBQW #1,(%0)\n"
            : : "d" (p)
        );
#elif defined(_LINUX) && defined(_ARM) 
	printf("Decrement (volatile int16 *p) NOT YET IMPLEMENTED for ARM1176rpi\n");

#elif (defined(_RTAI) || defined(_LINUX) || defined(_MACOSX))
        asm volatile(
            "lock decw (%0)\n"
            : : "r" (p)
            );
#elif defined(_SOLARIS)
// This is not appropriate .... but works for the moment...
    Atomic::PrivateLock();
    *p = *p - 1;
    Atomic::PrivateUnLock();
#else
#endif
    }

    /** Atomically decrement a 8 bit integer in memory. */
    static inline void Decrement (volatile int8 *p){
#if defined(_CINT)
#elif defined(_MSC_VER)
        __asm  {
            mov   ebx,p
            lock dec [ebx]
        }
#elif defined(_VX5100) || defined(_VX5500)|| defined(_V6X5100)|| defined(_V6X5500)

        volatile register int32 MSR, temp;
        asm volatile(
            "mfmsr %0\n"                // Gets the MSR
            "rlwinm %1,%0,0,17,15\n"    // Reset the EE flag to disable the interrupts
            "mtmsr %1\n"                // Update the MSR
            "lbzx %1,0,%2\n"            // Store *p in a register, otherwise it doesn't work
            "subi  %1,%1,1\n"           // Increment
            "stbx %1,0,%2\n"            // Store the result in *p
            "mtmsr %0"                  // Update the MSR
            :"=r" (MSR),"=r"(temp), "=r" (p) : "0" (MSR),"1"(temp), "2" (p)
        );
#elif defined(_VX68K)
        asm volatile(
            "SUBQB #1,(%0)\n"
            : : "d" (p)
        );
#elif defined(_LINUX) && defined(_ARM) 
	printf("Decrement (volatile int8 *p) NOT YET IMPLEMENTED for ARM1176rpi\n");

#elif (defined(_RTAI) || defined(_LINUX) || defined(_MACOSX))
        asm volatile(
            "lock decb (%0)\n"
            : : "r" (p)
            );
#elif defined(_SOLARIS)
// This is not appropriate .... but works for the moment...
    Atomic::PrivateLock();
    *p = *p - 1;
    Atomic::PrivateUnLock();
#else
#endif
    }

    /** Atomically exchange the contents of a variable with the specified memory location. */
    static inline int32 Exchange (volatile int32 *p, int32 v){
#if defined(_MSC_VER)
        __asm  {
            mov   ebx,p
            mov   eax,v
            lock xchg  DWORD PTR [ebx], eax
        }
#elif defined(_VX5100) || defined(_VX5500)|| defined(_V6X5100)|| defined(_V6X5500)


        volatile register int32 MSR,temp;
        asm volatile(
            "mfmsr %0\n"                // Gets the MSR
            "rlwinm %1,%0,0,17,15\n"    // Reset the EE flag to disable the interrupts
            "mtmsr %1\n"                // Update the MSR
            "lwarx %1,0,%3\n"           // Lock the resource
            "stwcx. %2,0,%3\n"          // Release the resource
            "bne- $-8\n"                // Repeat until atomic operation successful.
            "mr %2,%1\n"                // Swap
            "mtmsr %0"                  // Update the MSR
            : "=r" (MSR),"+r" (temp),"=r" (v) :"r" (p) , "2" (v)
        );
        return v;
#elif defined(_VX68K)
        int ret = *p;
        asm volatile(
            "MOVEL %1,(%0)"
            : "=d" (p) : "d" (v)
        );
        return ret;

#elif defined(_LINUX) && defined(_ARM) 
	 pa_atomic_cmpxchg((pa_atomic_t*)p, *p, v);

#elif defined(_RTAI)
        volatile int ret = *p;
        asm volatile(
            "lock xchg (%0), %1"
            : : "r" (p), "r" (v)
            );
        return ret;
#elif (defined(_LINUX) || defined(_MACOSX))
        asm volatile(
            "lock xchg (%1), %0"
            :"=r" (v) : "r" (p), "0" (v)
        );
        return v;
#endif
    }

    /** Test and set a 32 bit memory location in a thread safe way. */
    static inline bool TestAndSet(int32 volatile *p){
#if defined(_CINT)
        return 0;
#elif defined(_MSC_VER)
        int32 temp;
        __asm  {
            mov   ebx,p
            mov   eax,1
            xchg  DWORD PTR [ebx], eax
            mov   temp,eax
        }
        return (temp == 0);

#elif defined(_VX5100) || defined(_VX5500)|| defined(_V6X5100)|| defined(_V6X5500)

        volatile int32 MSR,out,temp;
        asm volatile(
            "mfmsr %1\n"                // Gets the MSR
            "rlwinm %2,%1,0,17,15\n"    // Reset the EE flag to disable the interrupts
            "mtmsr %2\n"                // Update the MSR
            "lwzx %0,0,%3\n"
            "li %2,1\n"
            "stwx %2,0,%3\n"
            "mtmsr %1"
            :"=r" (out),"=r" (MSR),"=r"(temp),"=r" (p) :"0" (out), "1" (MSR),"2"(temp), "3" (p)

        );
        return (out==0);
#elif (defined(_VX68K))
    volatile int8 out;
    asm volatile(
        "tas (%1)\n"
        "seq %0\n"
        :"=d" (out) : "g" (p)
        );

    return(out!=0);

#elif defined(_LINUX) && defined(_ARM) 
       return atomic_inc_and_test((pa_atomic_t *)p);
#elif (defined(_RTAI) || defined(_LINUX) || defined(_MACOSX))
    register int32 out=1;
    asm volatile (
        "lock xchg (%2),%1"
        : "=r" (out) : "0" (out), "r" (p)
        );
    return (out==0);
#elif defined(_SOLARIS)
// This is not appropriate .... but works for the moment...
    register int32 temp = 0;
    __asm__("ldstub [%1], %0"
        :  "=&r"(temp)
        :  "r"(p));

    return (temp==0);
#else
#endif
    }

    /** Test and set a 16 bit memory location in a thread safe way. */
    static inline bool TestAndSet(int16 volatile *p){
#if defined(_CINT)
        return 0;
#elif defined(_MSC_VER)
        int16 temp;
        __asm  {
            mov   ebx,p
            mov   ax,1
            xchg  WORD PTR [ebx], ax
            mov   temp,ax
        }
        return (temp == 0);

#elif defined(_VX5100) || defined(_VX5500)|| defined(_V6X5100)|| defined(_V6X5500)

        volatile int32 MSR;
        volatile int16 out,temp;
        asm volatile(
            "mfmsr %1\n"                // Gets the MSR
            "rlwinm %2,%1,0,17,15\n"    // Reset the EE flag to disable the interrupts
            "mtmsr %2\n"                // Update the MSR
            "lhzx %0,0,%3\n"
            "li %2,1\n"
            "sthx %2,0,%3\n"
            "mtmsr %1"
            :"=r" (out),"=r" (MSR),"=r"(temp),"=r" (p) :"0" (out), "1" (MSR),"2"(temp), "3" (p)
        );
        return (out==0);
#elif defined(_VX68K)
    volatile int8 out;
    asm volatile(
        "tas (%1)\n"
        "seq %0"
        :"=d" (out) :"g" (p)
    );
    return(out!=0);
#elif defined(_LINUX) && defined(_ARM) 

    printf("TestAndSet(int16  volatile *p) NOT YET IMPLEMENTED for ARM1176rpi\n");

#elif (defined(_RTAI) || defined(_LINUX) || defined(_MACOSX))
    register int16 out=1;
    asm volatile (
        "lock xchgw (%2),%1"
        : "=r" (out) : "0" (out), "r" (p)
        );
    return (out==0);
#elif defined(_SOLARIS)
    register int16 temp = 0;
    __asm__("ldstub [%1], %0"
        :  "=&r"(temp)
        :  "r"(p));

    return (temp==0);
#else
#endif
    }

    /** Test and set a 8 bit memory location in a thread safe way. */
    static inline bool TestAndSet(int8  volatile *p){
#if defined(_CINT)
        return 0;
#elif defined(_MSC_VER)
        int8 temp;
        __asm  {
            mov   ebx,p
            mov   al,1
            xchg   [ebx], al
            mov   temp,al
        }
        return (temp == 0);

#elif defined(_VX5100) || defined(_VX5500)|| defined(_V6X5100)|| defined(_V6X5500)

        volatile int32 MSR;
        volatile int8 out,temp;
        asm volatile(
            "mfmsr %1\n"                // Gets the MSR
            "rlwinm %2,%1,0,17,15\n"    // Reset the EE flag to disable the interrupts
            "mtmsr %2\n"                // Update the MSR
            "lbzx %0,0,%3\n"
            "li %2,1\n"
            "stbx %2,0,%3\n"
            "mtmsr %1"
            :"=r" (out),"=r" (MSR),"=r"(temp),"=r" (p) :"0" (out), "1" (MSR),"2"(temp), "3" (p)
        );
        return (out==0);
#elif defined(_VX68K)
    volatile int8 out;
    asm volatile(
        "tas (%1)\n"
        "seq %0"
        :"=d" (out)  :"g" (p)
    );
    return(out!=0);

#elif defined(_LINUX) && defined(_ARM) 

    printf("TestAndSet(int8  volatile *p) NOT YET IMPLEMENTED for ARM1176rpi\n");
#elif (defined(_RTAI) || defined(_LINUX) || defined(_MACOSX))
    register int8 out=1;
    asm volatile (
        "lock xchgb (%2),%1"
        : "=q" (out) : "0" (out), "q" (p)
        );
    return (out==0);
#elif defined(_SOLARIS)
// This is not appropriate .... but works for the moment...
    register int8 temp = 0;
    __asm__("ldstub [%1], %0"
        :  "=&r"(temp)
        :  "r"(p));

    return (temp==0);
#else
#endif
    }

    /**
     * Atomic addition
     */
    static inline void Add (volatile int32 *p, int32 value) {


#if defined(_LINUX) && defined(_ARM) 
	pa_atomic_add((pa_atomic_t *)p, value);
#elif (defined(_RTAI) || defined(_LINUX) || defined(_MACOSX))
        asm volatile (
                "lock addl %1, (%0)"
                : /* output */
                :"r" (p), "ir" (value) /* input */
        );
#elif defined(_SOLARIS)
// This is not appropriate .... but works for the moment...
    Atomic::PrivateLock();
    *p = *p + value;
    Atomic::PrivateUnLock();
#elif defined(_WIN32)
    __asm  {
        mov   ebx,p
        mov   eax,p
        lock add DWORD PTR[ebx], eax
    }
#else
    #error not available in this O.S. Contributions are welcome
#endif
    }

    /**
     * Atomic subtraction
     */
    static inline void Sub (volatile int32 *p, int32 value) {
#if defined(_LINUX) && defined(_ARM) 
	 pa_atomic_sub((pa_atomic_t *)p, value);

#elif (defined(_RTAI) || defined(_LINUX) || defined(_MACOSX))
        asm volatile (
                "lock subl %1, (%0)"
                : /* output */
                :"r" (p), "ir" (value) /* input */
        );
#elif defined(_SOLARIS)
// This is not appropriate .... but works for the moment...
    Atomic::PrivateLock();
    *p = *p - value;
    Atomic::PrivateUnLock();
#elif defined(_WIN32)
    __asm  {
        mov   ebx,p
        mov   eax,p
        lock add DWORD PTR[ebx], eax
    }
#else
    #error not available in this O.S. Contributions are welcome
#endif
    }

};

#endif

