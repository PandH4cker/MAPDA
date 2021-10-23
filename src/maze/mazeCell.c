//
// Created by drayr on 23/10/2021.
//

#include "../../includes/maze/mazeCell.h"
#include "../../includes/utils/bits.h"

inline bool isAboveUncrossable(MazeCell cell)
{
    return CHECK_BIT(cell, 3);
}

inline bool isBelowUncrossable(MazeCell cell)
{
    return CHECK_BIT(cell, 2);
}

inline bool isLeftUncrossable(MazeCell cell)
{
    return CHECK_BIT(cell, 1);
}

inline bool isRightUncrossable(MazeCell cell)
{
    return CHECK_BIT(cell, 0);
}

void printCell(MazeCell cell, WINDOW * win)
{
    int x = 0, y = 0;
    getyx(win, y, x);
    printw("(%d, %d)", x, y);
}
