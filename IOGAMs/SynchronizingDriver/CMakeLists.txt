message(STATUS " --SynchronizingDriver")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SynchronizingDriver)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/SynchronizingDriver)

add_library(SynchronizingDriver SHARED SynchronizingDriver.cpp  SynchronizingDriver.h )
target_link_libraries(SynchronizingDriver m dl nsl pthread rt ncurses)
target_link_libraries(SynchronizingDriver BaseLib2 MARTeSupportLib)
set_target_properties(SynchronizingDriver PROPERTIES HARED_LIBRARY_SUFFIX ".gam")