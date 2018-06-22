
message(STATUS " --GenericTimerDrv")

set(build_dir ${build_dir}/GenericTimerDriver)

add_library(GenericTimerDrv SHARED GenericTimerDrv.cpp  GenericTimerDrv.h )
target_link_libraries(GenericTimerDrv m dl nsl pthread rt ncurses)
target_link_libraries(GenericTimerDrv BaseLib2 MARTeSupportLib)