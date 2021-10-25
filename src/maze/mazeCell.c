//
// Created by drayr on 23/10/2021.
//

#include "../../includes/maze/mazeCell.h"
#include "../../includes/utils/bits.h"

void addAboveWall(CellValue * cellValue)
{
    SET_BIT(*cellValue, 3);
}

void addRightWall(CellValue * cellValue)
{
    SET_BIT(*cellValue, 2);
}

void addBelowWall(CellValue * cellValue)
{
    SET_BIT(*cellValue, 1);
}

void addLeftWall(CellValue * cellValue)
{
    SET_BIT(*cellValue, 0);
}

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