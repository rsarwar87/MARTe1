
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
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DFLAG_INTERFACE} ${DCXX_COMPILER_FLAG_EXE}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DFLAG_INTERFACE} ${DC_COMPILER_FLAG} ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DFLAG_INTERFACE} ${DC_COMPILER_FLAG} ")

add_definitions(-DUSE_PTHREAD)

set(CMAKE_LINK_LIBRARY_SUFFIX "")
set(CMAKE_EXECUTABLE_SUFFIX ".ex")     # lib
set(CMAKE_STATIC_LIBRARY_PREFIX "")     # lib
set(CMAKE_STATIC_LIBRARY_SUFFIX ".a")      # .a
set(CMAKE_SHARED_LIBRARY_PREFIX "")     # lib
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")     # .so


if(Interface_BaseLib2Adapter)
add_subdirectory(BaseLib2Adapter)
endif()
if(Interface_ConfigurationLibrary)
add_subdirectory(ConfigurationLibrary)
endif()
add_subdirectory(HTTP)
if(Interface_Logger_RelayLogger)
add_subdirectory(Logger/RelayLogger)
endif()

if(Interface_Logger_JTLogger)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Logger/JTLogger DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Looger)
endif()

if(Interface_MDSInterface)
#add_subdirectory(MDSInterface)
endif()
if(Interface_EPICSLib)
#add_subdirectory(EPICSlib)
endif()
if(Interface_RTAIConsole)
#add_subdirectory(RTAIConsole)
endif()
if(Interface_SimulinkInterface)
#add_subdirectory(SimulinkInterface)
endif()
if(Interface_TimeServiceActivities)
#add_subdirectory(TimeServiceActivities)
endif()
#logger-jt MDSInterface RTAIConsole SimulinkInterface
#add_subdirectory(MDSInterface)
#add_subdirectory(RTAIConsole)
#add_subdirectory(SimulinkInterface)
#add_subdirectory(TimeServiceActivities/MessageTriggeringTimeService)
