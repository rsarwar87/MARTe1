
message(STATUS " --Level3")

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_FILES2 ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(BaseLib3S STATIC ${SRC_FILES} ${SRC_FILES2} ${HDR_FILES})
target_link_libraries(BaseLib3S m dl nsl pthread rt ncurses)
target_link_libraries(BaseLib3S BaseLib0S BaseLib1S BaseLib2S)
