
project(BaseLib2)

message(STATUS "Starting to process BaseLib2")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_dir}/BaseLib2)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${build_dir}/BaseLib2)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${build_dir}/BaseLib2)

message (${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(Level0)
include_directories(Level1)
include_directories(Level2)
include_directories(Level3)
include_directories(Level4)
include_directories(Level5)
include_directories(Level6)
include_directories(LoggerService)


#TODO: Solaris, windows, vx  does not need this flag
#windows and vx have optimization flags
if (fLINUX) 
    set(CMAKE_CXX_FLAGS "${default_cxx_flag} -finline-functions -fPIC -frtti")
    set(CMAKE_C_FLAGS "${default_c_flag} -finline-functions -fPIC")
    set(CMAKE_CXX_FLAGS_DEBUG "${default_cxx_flag} -finline-functions -g -ggdb -fPIC")
    add_definitions(-D_LINUX)
endif()

if (fMAC) 
set(CMAKE_CXX_FLAGS "${default_cxx_flag} -finline-functions -fPIC -frtti")
set(CMAKE_C_FLAGS "${default_c_flag} -finline-functions -fPIC -frtti")
set(CMAKE_CXX_FLAGS_DEBUG "${default_cxx_flag} -finline-functions -g -fPIC")
endif()

add_definitions(-D_PTHREAD)

set(CMAKE_LINK_LIBRARY_SUFFIX "")
set(CMAKE_EXECUTABLE_SUFFIX ".ex")     # lib
set(CMAKE_STATIC_LIBRARY_PREFIX "lib")     # lib
set(CMAKE_STATIC_LIBRARY_SUFFIX ".a")      # .a
set(CMAKE_SHARED_LIBRARY_PREFIX "lib")     # lib
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")     # .so


add_subdirectory(Level0)
add_subdirectory(Level1)
add_subdirectory(Level2)
add_subdirectory(Level3)
add_subdirectory(Level4)
add_subdirectory(Level5)
add_subdirectory(Level6)
add_subdirectory(LoggerService)




file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_FILES2 ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(BaseLib2 SHARED )
target_link_libraries(BaseLib2 m dl nsl pthread rt ncurses)
target_link_libraries(BaseLib2 BLlvl0 BLlvl1 BLlvl2 BLlvl3 BLlvl4 BLlvl5 BLlvl6 LoggerService)