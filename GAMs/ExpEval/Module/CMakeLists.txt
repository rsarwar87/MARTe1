
message(STATUS "    --ModuleExpEval")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ExpEval/module)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/ExpEval/module)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_FILES2 ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)


add_library(ExpEval SHARED ${SRC_FILES} ${SRC_FILES2} ${HDR_FILES})
target_link_libraries(ExpEval m dl nsl pthread rt ncurses)
target_link_libraries(ExpEval BaseLib2 )
set_target_properties(ExpEval PROPERTIES SHARED_LIBRARY_PREFIX "lib"  SHARED_LIBRARY_SUFFIX ".so")