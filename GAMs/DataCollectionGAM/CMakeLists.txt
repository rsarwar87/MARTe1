
message(STATUS " --DataCollectionGAM")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DataCollectionGAM)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/DataCollectionGAM)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_FILES2 ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

add_library(CollectionGAMs SHARED ${SRC_FILES} ${SRC_FILES2} ${HDR_FILES})
target_link_libraries(CollectionGAMs m dl nsl pthread rt ncurses)
target_link_libraries(CollectionGAMs BaseLib2 ) 