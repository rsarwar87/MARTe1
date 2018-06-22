
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
if (fLINUX) 
    
    set(CMAKE_CXX_FLAGS "${default_cxx_flag} -fPIC -frtti -MMD -MP -MF -g -ggdb")
    set(CMAKE_C_FLAGS "${default_c_flag} -finline-functions -fPIC")
    set(CMAKE_CXX_FLAGS_DEBUG "${default_cxx_flag} -finline-functions -g -ggdb -fPIC")
    add_definitions(-D_LINUX)
endif()

if (fMAC) 
set(CMAKE_CXX_FLAGS "${default_cxx_flag} -finline-functions -fPIC -frtti")
set(CMAKE_C_FLAGS "${default_c_flag} -finline-functions -fPIC -frtti")
set(CMAKE_CXX_FLAGS_DEBUG "${default_cxx_flag} -finline-functions -g -fPIC")
endif()

add_definitions(-DUSE_PTHREAD)

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

add_subdirectory(GenericTimerDriver)
add_subdirectory(BinaryFileInput)
#add_subdirectory(CircularBufferSynchDriver)
add_subdirectory(LinuxTimer)
#add_subdirectory(LinuxATMDriver)
add_subdirectory(StreamingDriver)
add_subdirectory(SynchronizingDriver)

