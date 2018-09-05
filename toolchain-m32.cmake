# Define our host system
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)
# Define the cross compiler locations
SET(CMAKE_C_COMPILER   /usr/bin/gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/g++)
# Define the sysroot path for the m32 distribution in our tools folder 
SET(CMAKE_FIND_ROOT_PATH /usr/i686-linux-gnu)
# Use our definitions for compiler tools
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# Search for libraries and headers in the target directories only
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#add_definitions(-funsafe-math-optimizations -ffast-math -D_ARM -Wa,-mimplicit-it=thumb)

set(tm32 TRUE)
#set(CMAKE_CXX_COMPILER "-std-c11")
set(CMAKE_SYSTEM_PROCESSOR "i686")
set(CURSES_LIBRARY /usr/i686-linux-gnu/lib) 
set(CURSES_INCLUDE_PATH /usr/i686-linux-gnu/incluide)

