
message(STATUS " --WebStatisticGAM")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/WebStatisticGAM)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/WebStatisticGAM)



add_library(WebStatisticGAM SHARED WebStatisticGAM.cpp WebStatisticGAM.h )
target_link_libraries(WebStatisticGAM m dl nsl pthread rt ncurses)
target_link_libraries(WebStatisticGAM BaseLib2 )