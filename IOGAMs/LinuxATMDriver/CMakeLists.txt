
message(STATUS " --LinuxATMDriver")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LinuxATMDriver)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/LinuxATMDriver)

add_library(ATMDrv SHARED ATMDrv.cpp  ATMDrv.h )
target_link_libraries(ATMDrv m dl nsl pthread rt ncurses)
target_link_libraries(ATMDrv BaseLib2 MARTeSupportLib)

add_executable(ATMtest test.cpp  ATMDrv.h )
target_link_libraries(ATMtest m dl nsl pthread rt ncurses)
target_link_libraries(ATMtest BaseLib2 MARTeSupportLib)