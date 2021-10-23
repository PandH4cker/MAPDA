cmake_minimum_required(VERSION 3.13)
project(MAPDA C)

set(CMAKE_C_STANDARD 99)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(MAPDA src/main.c includes/maze/maze.h src/maze/mazeCell.c includes/utils/bits.h includes/maze/mazeCell.h includes/maze/init.h src/maze/init.c)
target_link_libraries(MAPDA ${CURSES_LIBRARIES})
