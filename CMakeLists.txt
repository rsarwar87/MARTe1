cmake_minimum_required(VERSION 3.2)

project(MARTe)

string (REGEX MATCH "\\.el[1-9]" os_version_suffix ${CMAKE_SYSTEM})

set(build_dir ${CMAKE_CURRENT_BINARY_DIR}/build_${CMAKE_SYSTEM_NAME}${os_version_suffix}_${CMAKE_SYSTEM_PROCESSOR})

set(default_cxx_flag ${CMAKE_CXX_FLAGS})
set(default_c_flag ${CMAKE_CXX_FLAGS})
set(default_cxx_flag_degug "${CMAKE_CXX_FLAGS_DEBUG} ")
set(default_c_flag_degug "${CMAKE_CXX_FLAGS_DEBUG} " )

OPTION(BUILD_TESTING "Build tests." OFF) #-D BUILD_TESTING:BOOL=TRUE

set(fLINUX FALSE )
set(fMAC FALSE)


if(UNIX AND NOT APPLE)
    if (APPLE)
        set(fMAC TRUE)
    else()
        set(fLINUX TRUE)
    endif()
endif()


if(fLINUX) 
    message(STATUS ">>> Detected Linux installation ${CMAKE_SYSTEM_PROCESSOR} ${os_version_suffix}")
    # linux stuff here
endif()
if(fMAC)
    message(STATUS ">>> Detected MacOS")
    # stuff that should happen not on Linux 
endif()
if(MSVC)
    message(STATUS ">>> Detected MSVC")
    # stuff that should happen not on Linux 
endif()

if(WIN32)
    message(STATUS ">>> Detected Win32")
    # stuff that should happen not on Linux 
endif()

# -lm -ldl -lnsl -lpthread -lrt -lncurses
find_package(Threads REQUIRED)
find_package(Curses REQUIRED)

add_subdirectory(BaseLib2)
add_subdirectory(GAMs/WebStatisticGAM)
add_subdirectory(Interfaces)

add_subdirectory(MARTe)