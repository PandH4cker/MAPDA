//
// Created by drayr on 23/10/2021.
//

#ifndef MAPDA_MAZE_H
#define MAPDA_MAZE_H

#include "mazeCell.h"

#define HORIZONTAL_PIPE "═"
#define HALF_ABOVE_HORIZONTAL_PIPE "╩"
#define HALF_BELOW_HORIZONTAL_PIPE "╦"
#define VERTICAL_PIPE "║"
#define HALF_RIGHT_VERTICAL_PIPE "╠"
#define HALF_LEFT_VERTICAL_PIPE "╣"
#define FULL_VERTICAL_PIPE "╬"
#define TOP_LEFT_CORNER "╔"
#define BOTTOM_LEFT_CORNER "╚"
#define TOP_RIGHT_CORNER "╗"
#define BOTTOM_RIGHT_CORNER "╝"
#define MAZE_ENTRYPOINT "E"
#define MAZE_OUT "S"


typedef struct Maze
{
    int nbLine, nbCol;
    Position entrypoint, out;
    MazeCell ** cells;
}Maze;

Maze newMaze(int line, int column, Position entrypoint, Position out);
Maze fromFile(const char * filename);
Maze randomMaze(int size);
void printMaze(WINDOW * win, Position startPrinting, Maze m);
void printCell(WINDOW *win, Position *startPrinting, Maze *maze, int line, int column);

#endif //MAPDA_MAZE_H
