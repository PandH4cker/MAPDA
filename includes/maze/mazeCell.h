//
// Created by drayr on 23/10/2021.
//

#ifndef MAPDA_MAZECELL_H
#define MAPDA_MAZECELL_H

#include <stdbool.h>

#if defined(__CYGWIN__) || defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__)
#include <curses.h>
#else
#include <ncurses.h>
#endif

typedef unsigned short MazeCell;

inline bool isAboveUncrossable(MazeCell cell);
inline bool isBelowUncrossable(MazeCell cell);
inline bool isLeftUncrossable(MazeCell cell);
inline bool isRightUncrossable(MazeCell cell);
void printCell(MazeCell cell, WINDOW * win);

#endif //MAPDA_MAZECELL_H
