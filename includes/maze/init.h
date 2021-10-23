//
// Created by drayr on 23/10/2021.
//

#ifndef MAPDA_INIT_H
#define MAPDA_INIT_H

#if defined(__CYGWIN__) || defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__)
#include <curses.h>
#else
#include <ncurses.h>
#endif

void ncursesInitColors();
void ncursesInit();
void ncursesInitMouse();

#endif //MAPDA_INIT_H
