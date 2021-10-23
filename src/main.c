#include <stdlib.h>

#include "../includes/utils/bits.h"
#include "../includes/maze/mazeCell.h"

int main(int argc, char ** argv) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();
    curs_set(FALSE);

    if(!mousemask(ALL_MOUSE_EVENTS, NULL))
    {
        endwin();
        fprintf(stderr, "Error while mouse initialization.\n");
        exit(EXIT_FAILURE);
    }
    if(has_mouse() != TRUE)
    {
        endwin();
        fprintf(stderr, "No mouse detected.\n");
        exit(EXIT_FAILURE);
    }

    if (has_colors() == FALSE)
    {
        endwin();
        fprintf(stderr, "The terminal does not support colors.\n");
        exit(EXIT_FAILURE);
    }

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(5, COLOR_BLUE,  COLOR_BLACK);
    init_pair(6, COLOR_YELLOW,COLOR_BLACK);

    MazeCell aboveWall = 0;
    SET_BIT(aboveWall, 3);

    MazeCell leftWall = 0;
    SET_BIT(leftWall, 2);

    MazeCell belowWall = 0;
    SET_BIT(belowWall, 1);

    MazeCell rightWall = 0;
    SET_BIT(rightWall, 0);

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
    /*printw("Above wall : %d\n", CHECK_BIT(aboveWall, 3));
    printw("Left wall : %d\n", CHECK_BIT(leftWall, 2));
    printw("Below wall : %d\n", CHECK_BIT(belowWall, 1));
    printw("Right wall : %d\n", CHECK_BIT(rightWall, 0));*/
    refresh();

    endwin();
    return EXIT_SUCCESS;
}
