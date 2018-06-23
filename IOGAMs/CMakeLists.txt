
project(IOGAMs)

message(STATUS "Starting to process IOGAMs")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_dir}/IOGAMs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${build_dir}/IOGAMs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${build_dir}/IOGAMs)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(../MARTe/MARTeSupportLib)
include_directories(../BaseLib2/Level0)
include_directories(../BaseLib2/Level1)
include_directories(../BaseLib2/Level2)
include_directories(../BaseLib2/Level3)
include_directories(../BaseLib2/Level4)
include_directories(../BaseLib2/Level5)
include_directories(../BaseLib2/Level6)
include_directories(../BaseLib2/LoggerService)


#TODO: Solaris, windows, vx  does not need this flag
#windows and vx have optimization flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DFLAG_IOGAMs} ${DCXX_COMPILER_FLAG_EXE}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DFLAG_IOGAMs} ${DC_COMPILER_FLAG} ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DFLAG_IOGAMs} ${DC_COMPILER_FLAG} ")
    

set(CMAKE_LINK_LIBRARY_SUFFIX "")
set(CMAKE_EXECUTABLE_SUFFIX ".ex")     # lib
set(CMAKE_STATIC_LIBRARY_PREFIX "")     # lib
set(CMAKE_STATIC_LIBRARY_SUFFIX ".a")      # .a
set(CMAKE_SHARED_LIBRARY_PREFIX "")     # lib
set(CMAKE_SHARED_LIBRARY_SUFFIX ".drv")     # .so



file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_FILES2 ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(IOGAMs SHARED ${SRC_FILES} ${SRC_FILES2} ${HDR_FILES})
target_link_libraries(IOGAMs m dl nsl pthread rt ncurses)
target_link_libraries(IOGAMs BaseLib2 MARTeSupportLib)

if(IOGAMS_GenericTimerDriver)
    add_subdirectory(GenericTimerDriver) 
endif()
if(IOGAMS_BinaryFileInput)
    add_subdirectory(BinaryFileInput)
endif()
if(IOGAMS_CircularBufferSynchDriver)
#add_subdirectory(CircularBufferSynchDriver)
endif()
if(IOGAMS_LinuxTimer)
    add_subdirectory(LinuxTimer)
endif()
if(IOGAMS_LinuxATMDriver)
    #add_subdirectory(LinuxATMDriver)
endif()
if(IOGAMS_StreamingDriver)
    add_subdirectory(StreamingDriver)
endif()
if(IOGAMS_SynchronizingDriver)
    add_subdirectory(SynchronizingDriver)
endif()
# udp SrTrATCADriver SimulationTimerDriver SharedMemoryDriver FileReaderDriver
