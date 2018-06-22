
message(STATUS " --StreamingDriver")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/StreamingDriver)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/StreamingDriver)

add_library(StreamingDriver SHARED StreamingDriver.cpp  StreamingDriver.h )
target_link_libraries(StreamingDriver m dl nsl pthread rt ncurses)
target_link_libraries(StreamingDriver BaseLib2 MARTeSupportLib)
set_target_properties(StreamingDriver PROPERTIES HARED_LIBRARY_SUFFIX ".gam")

add_library(StreamingDriverReceiver SHARED StreamingDriverReceiver.cpp  StreamingDriverReceiver.h )
target_link_libraries(StreamingDriverReceiver m dl nsl pthread rt ncurses)
target_link_libraries(StreamingDriverReceiver BaseLib2 MARTeSupportLib)
set_target_properties(StreamingDriverReceiver PROPERTIES HARED_LIBRARY_SUFFIX ".gam")

add_executable(ReceiverTest  ReceiverTest.cpp  StreamingDriverReceiver.h StreamingDriver.h )
target_link_libraries(ReceiverTest m dl nsl pthread rt ncurses)
target_link_libraries(ReceiverTest BaseLib2 MARTeSupportLib)