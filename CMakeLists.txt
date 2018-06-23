cmake_minimum_required(VERSION 3.2)


project(MARTe)

string (REGEX MATCH "\\.el[1-9]" os_version_suffix ${CMAKE_SYSTEM})




set(DLLEXT ".so")
set(DEBUG "-g")

set(fLINUX FALSE )
set(fMAC FALSE)
if(UNIX AND NOT APPLE)
    if (APPLE)
        set(fMAC TRUE)
        message(STATUS ">>> Detected Linux installation ${CMAKE_SYSTEM_PROCESSOR} ${os_version_suffix}")
        add_definitions(-D_LINUX)

        set(DCXX_FLAG "-fPIC -frtti")
        set(C_FLAG "-fPIC  -frtti")
        set(DLLEXT ".dylib")
    else()
        set(fLINUX TRUE)
        message(STATUS ">>> Detected MacOS")
        add_definitions(-D_LINUX)

        set(DLLEXT ".so")
        set(DEBUG "-g -ggdb")
        set(CXX_FLAG "-fPIC -frtti -MMD -MP -MF")
        set(C_FLAG "-fPIC ")
    endif()
elseif(fMAC)
    
    # stuff that should happen not on Linux 
elseif(MSVC)
    message(STATUS ">>> Detected MSVC")
    # stuff that should happen not on Linux 
elseif(WIN32)
    message(STATUS ">>> Detected Win32")
    set(DLLEXT ".dll")
    # stuff that should happen not on Linux 
endif()




OPTION(D_PTHREAD "Use pthread" ON)  
if(DPTHREAD)
    add_definitions(-DUSE_PTHREAD)
    add_definitions(-lpthread)
endif()

set(DC_COMPILER_FLAG "${C_FLAG} ${DEBUG} " 
    CACHE STRING "Common C compiler flag.")
set(DCXX_COMPILER_FLAG_EXE "${CXX_FLAG} ${DEBUG} " 
    CACHE STRING "Common CXX compiler flag.")



#BUILD Test scripts
OPTION(BUILD_VERBOSE "make verbose=1" OFF) 
set(CMAKE_VERBOSE_MAKEFILE  ${BUILD_VERBOSE}) 


set(BUILD_DIRECTORY build_${CMAKE_SYSTEM_NAME}${os_version_suffix}_${CMAKE_SYSTEM_PROCESSOR} 
                CACHE STRING "Location of the build folder")
set(BUILD_LOCATION ${CMAKE_CURRENT_BINARY_DIR} CACHE STRING "Name of the build folder")
set(build_dir ${BUILD_LOCATION}/${BUILD_DIRECTORY})

set(C_CINT_BINARY "" CACHE STRING "Location of the CINT Binary, not supported ATM; only a placeholder.")
set(C_CINT_LIB "" CACHE STRING "Location of the CINT library, not supported ATM; only a placeholder.")
set(C_CINT_SYSTEM "" CACHE STRING "Location of the CINT library, not supported ATM; only a placeholder.")
set(C_SDN_ROOT "" CACHE STRING "Location of the SDN library, not supported ATM; only a placeholder.")
set(C_JET_SHARED "" CACHE STRING "Location of the Jet libraries, not supported ATM; only a placeholder.")

set(DFLAG_BaseLib2 "-finline-functions" CACHE STRING "Special compiler flag for BaseLib2 library")
set(DFLAG_MARTe "" CACHE STRING "Special compiler flag for MARTe library")
set(DFLAG_GAMs "" CACHE STRING "Special compiler flag for GAMs libraries")
set(DFLAG_IOGAMs "" CACHE STRING "Special compiler flag for IOGAMs libraries")
set(DFLAG_INTERFACE "" CACHE STRING "Special compiler flag for Interface libraries.")


OPTION(INCLUDE_EXAMPLES "GAMs Package." ON) 

OPTION(GAMS_WaveformGenerator2009 "GAMs Package. " ON) 
OPTION(GAMS_WaterTank "GAMs Package." ON) 
OPTION(GAMS_StorageGAM "GAMs Package." ON)  
OPTION(GAMS_WebStatisticGAM "GAMs Package." ON)  
OPTION(GAMS_PlottingGAM "GAMs Package.." ON)  
OPTION(GAMS_DataCollectionGAM "GAMs Package." ON)  
OPTION(GAMS_PIDGAM "GAMs Package." ON) 
OPTION(GAMS_DelayGAM "GAMs Package." ON) 
OPTION(GAMS_StatisticGAM "GAMs Package." ON)  
OPTION(GAMS_DigitalFilterGAM "GAMs Package." ON) 
OPTION(GAMS_ExpEval "GAMs Package." ON) 
OPTION(GAMS_DigitalFilterGAM "GAMs Package." OFF) 
OPTION(GAMS_PlottingGAM "GAMs Package." OFF) 
OPTION(GAMS_SpringMassModel "GAMs Package." OFF) 
OPTION(GAMS_StateSpaceModel "GAMs Package." OFF) 
OPTION(GAMS_TypeConvertGAM "GAMs Package." OFF) 



OPTION(IOGAMS_GenericTimerDriver "GenericTimerDriver Package." ON)  
OPTION(IOGAMS_BinaryFileInput "BinaryFileInput Package." ON) 
OPTION(IOGAMS_LinuxTimer "LinuxTimer Package." ON) 
OPTION(IOGAMS_StreamingDriver "StreamingDriver Package." ON) 
OPTION(IOGAMS_SynchronizingDriver "SynchronizingDriver Package." ON) 
OPTION(IOGAMS_UDPDriver "UDPDriver Package." OFF) 
OPTION(IOGAMS_StreamingDriverSDN "StreamingDriverSDN Package." OFF) 
OPTION(IOGAMS_SrTrATCADriver  "SrTrATCADriver Package." OFF) 
OPTION(IOGAMS_SimulationTimerDriver "SimulationTimerDriver Package." OFF) 
OPTION(IOGAMS_SharedMemoryDriver "SharedMemoryDriver Package." OFF) 

OPTION(IOGAMS_SDNDriver "SDNDriver Package." OFF) 
OPTION(IOGAMS_ReplayDriver  "ReplayDriver Package." OFF) 
OPTION(IOGAMS_NI6368Driver "NI6368Driver  Package." OFF) 
OPTION(IOGAMS_NI6259Driver "NI6259Driver Package." OFF) 
OPTION(IOGAMS_MDSWriter "MDSWriter Package." OFF) 
OPTION(IOGAMS_LinuxATMDriver "LinuxATMDriver Package." OFF) 
OPTION(IOGAMS_FileWriterDriver "FileWriterDriver  Package." OFF) 
OPTION(IOGAMS_FileReaderDriver "FileReaderDriver Package." OFF) 
OPTION(IOGAMS_EPICSDrv "EPICSDrv Package." OFF) 
OPTION(IOGAMS_EPICSDriver "EPICSDriver Package." OFF) 
OPTION(IOGAMS_CircularBufferSynchDriver "CircularBufferSynchDriver Package." OFF) 
OPTION(IOGAMS_ATCAadc "EPICSDriver Package." OFF) 

OPTION(Interface_BaseLib2Adapter "BaseLib2Adapter Package." ON)  
OPTION(Interface_ConfigurationLibrary "ConfigurationLibrary Package." ON) 
OPTION(Interface_HTTP_CFGUploader "FGUploader Package." ON) 
OPTION(Interface_HTTP_FlotPlot "FlotPlot Package." ON) 
OPTION(Interface_HTTP_MATLABHandler "MATLABHandler Package." ON) 
OPTION(Interface_HTTP_SignalHandler "SignalHandler Package." ON) 
OPTION(Interface_Logger_RelayLogger "RelayLogger Package." ON) 
OPTION(Interface_Logger_JTLogger "JTLogger Package." ON) 
OPTION(Interface_MDSInterface "MDSInterface Package." OFF) 
OPTION(Interface_EPICSLib "EPICSLib Package." OFF) 
OPTION(Interface_RTAIConsole  "RTAIConsole Package." OFF) 
OPTION(Interface_SimulinkInterface "SimulinkInterface Package." OFF) 
OPTION(Interface_TimeServiceActivities "TimeServiceActivities Package." OFF) 






# -lm -ldl -lnsl -lpthread -lrt -lncurses
find_package(Threads REQUIRED)
find_package(Curses REQUIRED)

add_subdirectory(BaseLib2)
add_subdirectory(MARTe)
add_subdirectory(Interfaces)
add_subdirectory(IOGAMs)
add_subdirectory(GAMs)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Examples DESTINATION ${build_dir})
