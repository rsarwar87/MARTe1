
message(STATUS " --DigitalFilterGAM")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DigitalFilterGAM)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/DigitalFilterGAM)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_FILES2 ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)


add_library(DigitalFilterGAM SHARED ${SRC_FILES} ${SRC_FILES2} ${HDR_FILES})
target_link_libraries(DigitalFilterGAM m dl nsl pthread rt ncurses)
target_link_libraries(DigitalFilterGAM BaseLib2 )