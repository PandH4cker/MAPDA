#include <stdlib.h>

#include "../includes/utils/bits.h"
#include "../includes/maze/mazeCell.h"

int main(int argc, char ** argv) {
    ncursesInit();
    ncursesInitMouse();
    ncursesInitColors();

    MazeCell aboveWall = 0;
    SET_BIT(aboveWall, 3);

    MazeCell leftWall = 0;
    SET_BIT(leftWall, 2);

    MazeCell belowWall = 0;
    SET_BIT(belowWall, 1);

    MazeCell rightWall = 0;
    SET_BIT(rightWall, 0);

    do
    {
        int width, height, startY, startX;
        getmaxyx(stdscr, height, width);
        startX = startY = 0;

        WINDOW * win = NULL;
        win = newwin(height, width, startY, startX);
        refresh();
        char c = '#';
        box(win, (int)c, (int)c);
        wrefresh(win);
        wbkgd(win, COLOR_PAIR(3));
    } while (true);

    return EXIT_SUCCESS;
}
