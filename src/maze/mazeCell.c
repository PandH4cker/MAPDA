//
// Created by drayr on 23/10/2021.
//

#include "../../includes/maze/mazeCell.h"
#include "../../includes/utils/bits.h"

bool isAboveUncrossable(MazeCell cell)
{
    return CHECK_BIT(cell.cellValue, 3);
}

bool isRightUncrossable(MazeCell cell)
{
    return CHECK_BIT(cell.cellValue, 2);
}

bool isBelowUncrossable(MazeCell cell)
{
    return CHECK_BIT(cell.cellValue, 1);
}

bool isLeftUncrossable(MazeCell cell)
{
    return CHECK_BIT(cell.cellValue, 0);
}

void printCell(MazeCell cell, WINDOW * win)
{
    int x = 0, y = 0;
    getyx(win, y, x);
    printw("(%d, %d)", x, y);
}
