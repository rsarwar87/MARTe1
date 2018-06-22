

message(STATUS " --ExpEval")

add_subdirectory(Module)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ExpEval)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/ExpEval)

include_directories(Module)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_FILES2 ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)


add_library(ExpEvalGAM SHARED ${SRC_FILES} ${SRC_FILES2} ${HDR_FILES})
target_link_libraries(ExpEvalGAM m dl nsl pthread rt ncurses)
target_link_libraries(ExpEvalGAM BaseLib2 ExpEval) 