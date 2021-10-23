#include <stdlib.h>

#include "../includes/utils/bits.h"
#include "../includes/maze/mazeCell.h"

int main(int argc, char ** argv) {
    WINDOW * win = initscr();

    MazeCell aboveWall = 0;
    SET_BIT(aboveWall, 3);

    MazeCell leftWall = 0;
    SET_BIT(leftWall, 2);

    MazeCell belowWall = 0;
    SET_BIT(belowWall, 1);

    MazeCell rightWall = 0;
    SET_BIT(rightWall, 0);

    move(10,10);
    printw("TESTTTTTT\n");
    /*printw("Above wall : %d\n", CHECK_BIT(aboveWall, 3));
    printw("Left wall : %d\n", CHECK_BIT(leftWall, 2));
    printw("Below wall : %d\n", CHECK_BIT(belowWall, 1));
    printw("Right wall : %d\n", CHECK_BIT(rightWall, 0));*/
    refresh();

    endwin();
    return EXIT_SUCCESS;
}
