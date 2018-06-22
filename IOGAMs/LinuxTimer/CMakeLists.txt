
message(STATUS " --LinuxTimer")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LinuxTimer)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/LinuxTimer)

add_library(Timer SHARED LinuxTimerDrv.cpp  LinuxTimerDrv.h )
target_link_libraries(Timer m dl nsl pthread rt ncurses)
target_link_libraries(Timer BaseLib2 MARTeSupportLib)