
message(STATUS " --WaterTank")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/WaterTank)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/WaterTank)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_FILES2 ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)


add_library(WaterTank SHARED ${SRC_FILES} ${SRC_FILES2} ${HDR_FILES} )
target_link_libraries(WaterTank m dl nsl pthread rt ncurses)
target_link_libraries(WaterTank BaseLib2)