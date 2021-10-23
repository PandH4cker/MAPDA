cmake_minimum_required(VERSION 3.20)
project(MAPDA C)

set(CMAKE_C_STANDARD 99)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(MAPDA src/main.c includes/maze/maze.h src/maze/mazeCell.c includes/utils/bits.h includes/maze/mazeCell.h)
target_link_libraries(MAPDA ${CURSES_LIBRARIES})
