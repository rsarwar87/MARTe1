
message(STATUS " --BinaryFileInput")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CircularBufferSynchDriver)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/CircularBufferSynchDriver)

add_library(BinaryFileInputGAM SHARED BinaryFileInputGAM.cpp  BinaryFileInputGAM.h )
target_link_libraries(BinaryFileInputGAM m dl nsl pthread rt ncurses)
target_link_libraries(BinaryFileInputGAM BaseLib2 MARTeSupportLib)

add_library(BinaryFileTimeInputGAM SHARED BinaryFileTimeInputGAM.cpp  BinaryFileTimeInputGAM.h )
target_link_libraries(BinaryFileTimeInputGAM m dl nsl pthread rt ncurses)
target_link_libraries(BinaryFileTimeInputGAM BaseLib2 MARTeSupportLib)