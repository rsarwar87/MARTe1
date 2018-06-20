
message(STATUS " --Logger")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Logger/RelayLogger)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Logger/RelayLogger)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Looger/RelayLogger)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_FILES2 ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)



add_library(RelayLogger SHARED ${SRC_FILES}  ${SRC_FILES2} ${HDR_FILES})
target_link_libraries(RelayLogger m dl nsl pthread rt ncurses)
target_link_libraries(RelayLogger  BaseLib2 )


add_executable(RelayLog RelayLog  RelayLog/RelayLogger.cpp ${HDR_FILES})
target_link_libraries(RelayLog m dl nsl pthread rt ncurses)
target_link_libraries(RelayLog  RelayLogger BaseLib2 )



add_library(RelayLoggerService SHARED RelayLoggerService_/RelayLoggerService.cpp  RelayLoggerService_/RelayLoggerService.h ${HDR_FILES})
target_link_libraries(RelayLoggerService m dl nsl pthread rt ncurses)
target_link_libraries(RelayLoggerService BaseLib2 )