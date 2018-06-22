
message(STATUS " --HTTP")


include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${build_dir}/Interfaces/HTTP/CFGUploader)
add_library(CFGUploader SHARED CFGUploader/CFGUploader.cpp  CFGUploader/CFGUploader.h)
target_link_libraries(CFGUploader m dl nsl pthread rt ncurses)
target_link_libraries(CFGUploader  BaseLib2 )
set(COMM3 ln -sf ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/CFGUploader.so  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libCFGUploader.so)
add_custom_command(TARGET  CFGUploader POST_BUILD COMMAND ${COMM3})


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${build_dir}/Interfaces/HTTP/FlotPlot)

add_library(FlotPlot SHARED FlotPlot/FlotPlot.cpp  FlotPlot/FlotPlot.h)
target_link_libraries(FlotPlot m dl nsl pthread rt ncurses)
target_link_libraries(FlotPlot  BaseLib2 )
set(COMM3 ln -sf ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/FlotPlot.so  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libFlotPlot.so)
add_custom_command(TARGET  FlotPlot POST_BUILD COMMAND ${COMM3})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${build_dir}/Interfaces/HTTP/MATLABHandler)
add_library(MATLABHandler SHARED MATLABHandler/MATLABHandler.cpp  MATLABHandler/MATLABHandler.h)
target_link_libraries(MATLABHandler m dl nsl pthread rt ncurses)
target_link_libraries(MATLABHandler  BaseLib2 )
set(COMM3 ln -sf ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/MATLABHandler.so  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libMATLABHandler.so)
add_custom_command(TARGET  MATLABHandler POST_BUILD COMMAND ${COMM3})


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${build_dir}/Interfaces/HTTP/SignalHandler)
add_library(SignalServer SHARED SignalHandler/SignalServer.cpp  SignalHandler/SignalServer.h)
target_link_libraries(SignalServer m dl nsl pthread rt ncurses)
target_link_libraries(SignalServer  BaseLib2 )
set(COMM3 ln -sf ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/SignalServer.so  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libSignalServer.so)
add_custom_command(TARGET  SignalServer POST_BUILD COMMAND ${COMM3})