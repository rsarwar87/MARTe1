
message(STATUS " --MDSInterface")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MDSInterface)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MDSInterface)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MDSInterface)


add_library(MDSInterface SHARED MDSInterface.cpp  MDSInterface.h )
target_link_libraries(MDSInterface m dl nsl pthread rt ncurses)
target_link_libraries(MDSInterface BaseLib2 )