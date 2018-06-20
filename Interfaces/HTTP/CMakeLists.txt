
message(STATUS " --HTTP")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/HTTP)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/HTTP)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/HTTP)



add_library(CFGUploader SHARED CFGUploader/CFGUploader.cpp  CFGUploader/CFGUploader.h)
target_link_libraries(CFGUploader m dl nsl pthread rt ncurses)
target_link_libraries(CFGUploader  BaseLib2 )



add_library(FlotPlot SHARED FlotPlot/FlotPlot.cpp  FlotPlot/FlotPlot.h)
target_link_libraries(FlotPlot m dl nsl pthread rt ncurses)
target_link_libraries(FlotPlot  BaseLib2 )

add_library(MATLABHandler SHARED MATLABHandler/MATLABHandler.cpp  MATLABHandler/MATLABHandler.h)
target_link_libraries(MATLABHandler m dl nsl pthread rt ncurses)
target_link_libraries(MATLABHandler  BaseLib2 )


add_library(SignalHandler SHARED SignalHandler/SignalServer.cpp  SignalHandler/SignalServer.h)
target_link_libraries(SignalHandler m dl nsl pthread rt ncurses)
target_link_libraries(SignalHandler  BaseLib2 )