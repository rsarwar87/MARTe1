
message(STATUS " --Level6")

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_FILES2 ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)


add_library(BLlvl6 STATIC ${SRC_FILES} ${SRC_FILES2} ${HDR_FILES})
target_link_libraries(BLlvl6 m dl nsl pthread rt ncurses)
target_link_libraries(BLlvl6 BLlvl0 BLlvl1 BLlvl2 BLlvl3 BLlvl4 BLlvl5)

