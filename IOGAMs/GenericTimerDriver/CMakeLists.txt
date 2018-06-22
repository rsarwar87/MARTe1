
message(STATUS " --GenericTimerDrv")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GenericTimerDrv)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/GenericTimerDrv)

add_library(GenericTimerDrv SHARED GenericTimerDrv.cpp  GenericTimerDrv.h )
target_link_libraries(GenericTimerDrv m dl nsl pthread rt ncurses)
target_link_libraries(GenericTimerDrv BaseLib2 MARTeSupportLib)