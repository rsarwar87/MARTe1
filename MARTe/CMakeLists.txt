
project(Interfaces)

message(STATUS "Starting to process MARTe")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_dir}/MARTe)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${build_dir}/MARTe)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${build_dir}/MARTe)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(../BaseLib2/Level0)
include_directories(../BaseLib2/Level1)
include_directories(../BaseLib2/Level2)
include_directories(../BaseLib2/Level3)
include_directories(../BaseLib2/Level4)
include_directories(../BaseLib2/Level5)
include_directories(../BaseLib2/Level6)
include_directories(../BaseLib2/LoggerService)
include_directories(MARTeSupportLib)

#TODO: Solaris, windows, vx  does not need this flag
#windows and vx have optimization flags
if (fLINUX) 
    set(CMAKE_CXX_FLAGS "${default_cxx_flag}  -g -ggdb -MMD -MP -MF  -fPIC -frtti")
    set(CMAKE_C_FLAGS "${default_c_flag}  -fPIC")
    set(CMAKE_CXX_FLAGS_DEBUG "${default_cxx_flag} -MMD -MP -MF  -g -ggdb -fPIC")
    add_definitions(-D_LINUX)
endif()

if (fMAC) 
set(CMAKE_CXX_FLAGS "${default_cxx_flag}-fPIC -frtti")
set(CMAKE_C_FLAGS "${default_c_flag}  -fPIC -frtti")
set(CMAKE_CXX_FLAGS_DEBUG "${default_cxx_flag} -MMD -MP -MF  -g -fPIC")
endif()

add_definitions(-D_PTHREAD)

set(CMAKE_LINK_LIBRARY_SUFFIX "")
set(CMAKE_EXECUTABLE_SUFFIX ".ex")     # lib
set(CMAKE_STATIC_LIBRARY_PREFIX "")     # lib
set(CMAKE_STATIC_LIBRARY_SUFFIX ".a")      # .a
set(CMAKE_SHARED_LIBRARY_PREFIX "")     # lib
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")     # .so

add_subdirectory(MARTeSupportLib)




message(STATUS " --MARTe")


add_executable(MARTe MARTe.cpp  MARTe.h )
target_link_libraries(MARTe m dl nsl pthread rt ncurses)
target_link_libraries(MARTe BaseLib2 MARTeSupportLib)

add_executable(MARTeService MARTeService.cpp  MARTeService.h )
target_link_libraries(MARTeService m dl nsl pthread rt ncurses)
target_link_libraries(MARTeService BaseLib2 MARTeSupportLib)
