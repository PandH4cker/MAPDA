//
// Created by drayr on 23/10/2021.
//

#ifndef MAPDA_MAZECELL_H
#define MAPDA_MAZECELL_H

#include <stdbool.h>

#include "init.h"

typedef unsigned short CellValue;

typedef struct Position
{
    int x,y;
}Position;

typedef struct MazeCell
{
    CellValue cellValue;
    Position p;
}MazeCell;

bool isAboveUncrossable(MazeCell cell);
bool isBelowUncrossable(MazeCell cell);
bool isLeftUncrossable(MazeCell cell);
bool isRightUncrossable(MazeCell cell);
void printCell(MazeCell cell, WINDOW * win);

#endif //MAPDA_MAZECELL_H
