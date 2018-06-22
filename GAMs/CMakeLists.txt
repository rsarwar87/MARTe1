
project(GAMs)

message(STATUS "Starting to process GAMs")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${build_dir}/GAMs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${build_dir}/GAMs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${build_dir}/GAMs)


include_directories(../BaseLib2/LoggerService)
include_directories(../BaseLib2/Level0)
include_directories(../BaseLib2/Level1)
include_directories(../BaseLib2/Level2)
include_directories(../BaseLib2/Level3)
include_directories(../BaseLib2/Level4)
include_directories(../BaseLib2/Level5)
include_directories(../BaseLib2/Level6)


#TODO: Solaris, windows, vx  does not need this flag
#windows and vx have optimization flags
if (fLINUX)
    set(CMAKE_CXX_FLAGS "${default_cxx_flag} -fPIC -frtti -MMD -MP -MF -g -ggdb")
    set(CMAKE_C_FLAGS "${default_c_flag} -fPIC")
    set(CMAKE_CXX_FLAGS_DEBUG "${default_cxx_flag}  -g -ggdb -fPIC")
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
set(CMAKE_STATIC_LIBRARY_SUFFIX ".gam")      # .a
set(CMAKE_SHARED_LIBRARY_PREFIX "")     # lib
set(CMAKE_SHARED_LIBRARY_SUFFIX ".gam")     # .so


add_subdirectory(WaveformGenerator2009)
add_subdirectory(WaterTank)
add_subdirectory(StorageGAM)
add_subdirectory(WebStatisticGAM)
add_subdirectory(PlottingGAM)
add_subdirectory(StatisticGAM)
add_subdirectory(DataCollectionGAM)
add_subdirectory(PIDGAM)
add_subdirectory(DelayGAM)
add_subdirectory(DigitalFilterGAM)
add_subdirectory(ExpEval)

#delaygam  DigitalFilterGAM  ExpEval  :
