
message(STATUS " --MARTeSupportLib")


file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_FILES2 ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)


add_library(MARTeSupportLib SHARED ${SRC_FILES} ${SRC_FILES2} ${HDR_FILES})
target_link_libraries(MARTeSupportLib m dl nsl pthread rt ncurses)
target_link_libraries(MARTeSupportLib  BaseLib2 )
