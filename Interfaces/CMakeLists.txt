
project(Interfaces)

message(STATUS "Starting to process Interfaces")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_dir}/Interfaces)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${build_dir}/Interfaces)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${build_dir}/Interfaces)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
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
    set(CMAKE_CXX_FLAGS "${default_cxx_flag} -O2  -finline-functions -fPIC -frtti")
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
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")     # .so

add_subdirectory(BaseLib2Adapter)
add_subdirectory(ConfigurationLibrary)
#add_subdirectory(EPICSlib)
add_subdirectory(HTTP)
add_subdirectory(Logger/RelayLogger)
#add_subdirectory(MDSInterface)
#add_subdirectory(RTAIConsole)
#add_subdirectory(SimulinkInterface)
#add_subdirectory(TimeServiceActivities/MessageTriggeringTimeService)
