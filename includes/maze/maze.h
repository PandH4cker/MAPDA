//
// Created by drayr on 23/10/2021.
//

#ifndef MAPDA_MAZE_H
#define MAPDA_MAZE_H

#include "mazeCell.h"

typedef struct Maze
{
    int nbLine, nbCol;
    Position entrypoint, out;
    MazeCell ** cells;
}Maze;

Maze fromFile(const char * filename);

#endif //MAPDA_MAZE_H
