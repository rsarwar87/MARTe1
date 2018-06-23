
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



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DFLAG_GAMs} ${DCXX_COMPILER_FLAG_EXE}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DFLAG_GAMs} ${DC_COMPILER_FLAG} ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DFLAG_GAMs} ${DC_COMPILER_FLAG} ")
    

add_definitions(-DUSE_PTHREAD)

set(CMAKE_LINK_LIBRARY_SUFFIX "")
set(CMAKE_EXECUTABLE_SUFFIX ".ex")     
set(CMAKE_STATIC_LIBRARY_PREFIX "")     # lib
set(CMAKE_STATIC_LIBRARY_SUFFIX ".gam")      # .a
set(CMAKE_SHARED_LIBRARY_PREFIX "")     # lib
set(CMAKE_SHARED_LIBRARY_SUFFIX ".gam")     # .so


if(GAMS_WaveformGenerator2009)
add_subdirectory(WaveformGenerator2009)
endif()
if(GAMS_WaterTank)
add_subdirectory(WaterTank)
endif()
if(GAMS_StorageGAM)
add_subdirectory(StorageGAM)
endif()
if(GAMS_WebStatisticGAM)
add_subdirectory(WebStatisticGAM)
endif()
if(GAMS_PlottingGAM)
add_subdirectory(PlottingGAM)
endif()
if(GAMS_StatisticGAM)
add_subdirectory(StatisticGAM)
endif()
if(GAMS_DataCollectionGAM)
add_subdirectory(DataCollectionGAM)
endif()
if(GAMS_PIDGAM)
add_subdirectory(PIDGAM)
endif()
if(GAMS_DelayGAM)
add_subdirectory(DelayGAM)
endif()
if(GAMS_DigitalFilterGAM)
add_subdirectory(DigitalFilterGAM)
endif()
if(GAMS_ExpEval)
add_subdirectory(ExpEval)
endif()

