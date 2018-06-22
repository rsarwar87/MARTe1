
message(STATUS " --ConfigurationLibrary")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConfigurationLibrary)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConfigurationLibrary)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConfigurationLibrary)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_FILES2 ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(ConfigurationLibrary SHARED ${SRC_FILES} ${SRC_FILES2} ${HDR_FILES})
target_link_libraries(ConfigurationLibrary m dl nsl pthread rt ncurses)
target_link_libraries(ConfigurationLibrary  BaseLib2 )
set_target_properties(ConfigurationLibrary  PROPERTIES PREFIX "")



add_library(GenericTestGAM SHARED GenericTest/GenericTestGAM.cpp  ${HDR_FILES})
target_link_libraries(GenericTestGAM m dl nsl pthread rt ncurses )
target_link_libraries(GenericTestGAM  BaseLib2 ConfigurationLibrary)
set_target_properties(GenericTestGAM  PROPERTIES SUFFIX ".gam")


add_executable(MessageSender MessageSender/main.cpp ${HDR_FILES})
target_link_libraries(MessageSender m dl nsl pthread rt ncurses)
target_link_libraries(MessageSender  BaseLib2 ConfigurationLibrary)