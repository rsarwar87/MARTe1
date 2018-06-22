
message(STATUS " --CircularBufferSynchDriver")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CircularBufferSynchDriver)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LinuxTimer)
set(build_dir ${build_dir}/BinaryFileInput)
include_directories(/usr/local/mdsplus/include)

add_library(CircularBufferSynchDrv SHARED CircularBufferSynchDrv.cpp  CircularBufferSynchDrv.h )
target_link_libraries(CircularBufferSynchDrv m dl nsl pthread rt ncurses)
target_link_libraries(CircularBufferSynchDrv BaseLib2 MARTeSupportLib MdsObjectsCppShr)

