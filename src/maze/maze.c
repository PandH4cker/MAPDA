//
// Created by drayr on 23/10/2021.
//

#include <stdlib.h>

#include "../../includes/utils/bits.h"
#include "../../includes/maze/maze.h"
#include "../../includes/utils/random.h"

Maze randomMaze(int width, int height)
{
    Maze maze = newMaze(width, height, (Position) {.x = RAND(0, height - 1),.y = RAND(0, width - 1)},
                        (Position) {.x = RAND(0, height - 1),.y = RAND(0, width - 1)});
    for (int i = 0; i < maze.nbLine; ++i)
        for (int j = 0; j < maze.nbCol; ++j)
        {
            maze.cells[i][j].cellValue = 15;
            maze.cells[i][j].p.x = i;
            maze.cells[i][j].p.y = j;
        }
    for (int i = 0; i < maze.nbLine; ++i)
        for (int j = 0; j < maze.nbCol; ++j)
        {
            CellValue wallToBreak;
            if (i == 0)
            {
                if (j == 0)
                {
                    wallToBreak = EVEN_RAND(0, 2);
                    SET_BIT(wallToBreak, 0);
                    SET_BIT(wallToBreak, 3);
                }
                else if (j != maze.nbCol - 1)
                {
                    wallToBreak = EVEN_RAND(0, 8);
                    SET_BIT(wallToBreak, 3);
                    if (isRightUncrossable(maze.cells[i][j - 1]))
                        addLeftWall(&wallToBreak);
                    else if (CHECK_BIT(wallToBreak, 0))
                        addRightWall(&maze.cells[i][j - 1].cellValue);
                }
                else
                {
                    wallToBreak = RAND(0, 3);
                    SET_BIT(wallToBreak, 3);
                    SET_BIT(wallToBreak, 2);
                    if (isRightUncrossable(maze.cells[i][j - 1]))
                        addLeftWall(&wallToBreak);
                    else if (CHECK_BIT(wallToBreak, 0))
                        addRightWall(&maze.cells[i][j - 1].cellValue);
                }
            }
            else if (i != maze.nbLine - 1)
            {
                if (j == 0)
                {
                    wallToBreak = EVEN_RAND(0, 8);
                    SET_BIT(wallToBreak, 0);
                    if (isBelowUncrossable(maze.cells[i - 1][j]))
                        addAboveWall(&wallToBreak);
                    else if (CHECK_BIT(wallToBreak, 3))
                        addBelowWall(&maze.cells[i - 1][j].cellValue);
                }
                else if (j != maze.nbCol - 1)
                {
                    wallToBreak = EVEN_RAND(0, 8);
                    if (isBelowUncrossable(maze.cells[i - 1][j]))
                        addAboveWall(&wallToBreak);
                    else if (CHECK_BIT(wallToBreak, 3))
                        addBelowWall(&maze.cells[i - 1][j].cellValue);

                    if (isRightUncrossable(maze.cells[i][j - 1]))
                        addLeftWall(&wallToBreak);
                    else if (CHECK_BIT(wallToBreak, 0))
                        addRightWall(&maze.cells[i][j - 1].cellValue);
                }
                else
                {
                    wallToBreak = EVEN_RAND(0, 8);
                    SET_BIT(wallToBreak, 2);
                    if (isBelowUncrossable(maze.cells[i - 1][j]))
                        addAboveWall(&wallToBreak);
                    else if (CHECK_BIT(wallToBreak, 3))
                        addBelowWall(&maze.cells[i - 1][j].cellValue);

                    if (isRightUncrossable(maze.cells[i][j - 1]))
                        addLeftWall(&wallToBreak);
                    else if (CHECK_BIT(wallToBreak, 0))
                        addRightWall(&maze.cells[i][j - 1].cellValue);
                }
            }
            else
            {
                if (j == 0)
                {
                    wallToBreak = EVEN_RAND(0, 8);
                    SET_BIT(wallToBreak, 0);
                    SET_BIT(wallToBreak, 1);
                    if (isBelowUncrossable(maze.cells[i - 1][j]))
                        addAboveWall(&wallToBreak);
                    else if (CHECK_BIT(wallToBreak, 3))
                        addBelowWall(&maze.cells[i - 1][j].cellValue);
                }
                else if (j != maze.nbCol - 1)
                {
                    wallToBreak = EVEN_RAND(0, 8);
                    SET_BIT(wallToBreak, 1);
                    if (isRightUncrossable(maze.cells[i][j - 1]))
                        addLeftWall(&wallToBreak);
                    else if (CHECK_BIT(wallToBreak, 0))
                        addRightWall(&maze.cells[i][j - 1].cellValue);

                    if (isBelowUncrossable(maze.cells[i - 1][j]))
                        addAboveWall(&wallToBreak);
                    else if (CHECK_BIT(wallToBreak, 3))
                        addBelowWall(&maze.cells[i - 1][j].cellValue);
                }
                else
                {
                    wallToBreak = EVEN_RAND(0, 8);
                    SET_BIT(wallToBreak, 1);
                    SET_BIT(wallToBreak, 2);
                    if (isBelowUncrossable(maze.cells[i - 1][j]))
                        addAboveWall(&wallToBreak);
                    else if (CHECK_BIT(wallToBreak, 3))
                        addBelowWall(&maze.cells[i - 1][j].cellValue);

                    if (isRightUncrossable(maze.cells[i][j - 1]))
                        addLeftWall(&wallToBreak);
                    else if (CHECK_BIT(wallToBreak, 0))
                        addRightWall(&maze.cells[i][j - 1].cellValue);
                }
            }
            maze.cells[i][j].cellValue = wallToBreak;
        }
    return maze;
}

Maze newMaze(int line, int column, Position entrypoint, Position out)
{
    Maze maze;
    maze.entrypoint = entrypoint;
    maze.out = out;
    maze.nbLine = line;
    maze.nbCol = column;

    maze.cells = calloc(maze.nbLine, sizeof(MazeCell*));
    for (int i = 0; i < maze.nbLine; ++i) maze.cells[i] = calloc(maze.nbCol, sizeof (MazeCell));
    return maze;
}

Maze fromFile(const char * filename)
{
    FILE * f = fopen(filename, "r");
    if(!f)
    {
        fprintf(stderr, "Impossible to open %s, file does not exist.\n", filename);
        exit(EXIT_FAILURE);
    }
    rewind(f);
    Position entrypoint, out;
    int nbLine, nbCol;

    if (fscanf(f, "%d%d%d%d%d%d", &nbLine, &nbCol, &entrypoint.x, &entrypoint.y, &out.x, &out.y) != EOF)
    {
        Maze maze = newMaze(nbLine, nbCol, entrypoint, out);

        for (int i = 0; i < maze.nbLine; ++i)
            for (int j = 0; j < maze.nbCol; ++j)
            {
                if(fscanf(f, "%hd", &maze.cells[i][j].cellValue) == EOF)
                {
                    fprintf(stderr, "ERROR: File malformed !\n");
                    exit(EXIT_FAILURE);
                }
                maze.cells[i][j].p.x = i;
                maze.cells[i][j].p.y = j;
            }

        fclose(f);
        return maze;
    }
    else
    {
        fprintf(stderr, "Error occurred while reading the file\n");
        exit(EXIT_FAILURE);
    }
}

void printMaze(WINDOW * win, Position startPrinting, Maze m)
{
    for (int i = 0; i < m.nbLine; ++i)
    {
        for (int j = 0; j < m.nbCol; ++j)
        {
            printCell(win, &startPrinting, &m, i, j);
            startPrinting.x += 2;
        }
        startPrinting.x = 5;
        startPrinting.y += 2;
    }
}

void printCell(WINDOW *win, Position *startPrinting, Maze *maze, int line, int column) {
    if (isLeftUncrossable(maze->cells[line][column]))
    {
        mvwprintw(win, startPrinting->y, startPrinting->x - 1, VERTICAL_PIPE);
        if (column == 0 && line != maze->nbLine - 1) // Left border
        {
            if (isBelowUncrossable(maze->cells[line][column]))
                mvwprintw(win, startPrinting->y + 1, startPrinting->x - 1, HALF_RIGHT_VERTICAL_PIPE);
            else
                mvwprintw(win, startPrinting->y + 1, startPrinting->x - 1, VERTICAL_PIPE);
        }
        else if (column != 0 && line != maze->nbLine - 1) // Inside border
        {
            if (isBelowUncrossable(maze->cells[line][column]))
            {
                if ((line+1) < maze->nbLine && (column - 1) >= 0 &&
                    isBelowUncrossable(maze->cells[line][column - 1]) &&
                    isLeftUncrossable(maze->cells[line + 1][column]))
                    mvwprintw(win, startPrinting->y + 1, startPrinting->x - 1, FULL_VERTICAL_PIPE);
                else if ((line+1) < maze->nbLine && (column - 1) >= 0 &&
                         !isBelowUncrossable(maze->cells[line][column - 1]) &&
                         isLeftUncrossable(maze->cells[line + 1][column]))
                    mvwprintw(win, startPrinting->y + 1, startPrinting->x - 1, HALF_RIGHT_VERTICAL_PIPE);
                else if ((line+1) < maze->nbLine && (column - 1) >= 0 &&
                         isBelowUncrossable(maze->cells[line][column - 1]) &&
                         !isLeftUncrossable(maze->cells[line + 1][column]))
                    mvwprintw(win, startPrinting->y + 1, startPrinting->x - 1, HALF_ABOVE_HORIZONTAL_PIPE);
                else
                    mvwprintw(win, startPrinting->y + 1, startPrinting->x - 1, BOTTOM_LEFT_CORNER);
            }
            else
            {
                if ((line+1) < maze->nbLine && (column - 1) >= 0 &&
                    isBelowUncrossable(maze->cells[line][column - 1]) &&
                    isLeftUncrossable(maze->cells[line + 1][column]))
                    mvwprintw(win, startPrinting->y + 1, startPrinting->x - 1, HALF_LEFT_VERTICAL_PIPE);
                else if ((line+1) < maze->nbLine && (column - 1) >= 0 &&
                         isBelowUncrossable(maze->cells[line][column - 1]) &&
                         !isLeftUncrossable(maze->cells[line + 1][column]))
                    mvwprintw(win, startPrinting->y + 1, startPrinting->x - 1, BOTTOM_RIGHT_CORNER);
                else
                    mvwprintw(win, startPrinting->y + 1, startPrinting->x - 1, VERTICAL_PIPE);
            }

            if (isAboveUncrossable(maze->cells[line][column]) && line != 0)
            {
                if ((line-1) >= 0 && (column-1) >= 0 &&
                    isLeftUncrossable(maze->cells[line - 1][column]) &&
                    isBelowUncrossable(maze->cells[line - 1][column - 1]))
                    mvwprintw(win, startPrinting->y - 1, startPrinting->x - 1, FULL_VERTICAL_PIPE);
                else if ((line-1) >= 0 && (column-1) >= 0 &&
                         !isLeftUncrossable(maze->cells[line - 1][column]) &&
                         isBelowUncrossable(maze->cells[line - 1][column - 1]))
                    mvwprintw(win, startPrinting->y - 1, startPrinting->x - 1, HALF_BELOW_HORIZONTAL_PIPE);
                else if ((line-1) >= 0 && (column-1) >= 0 &&
                         isLeftUncrossable(maze->cells[line - 1][column]) &&
                         !isBelowUncrossable(maze->cells[line - 1][column - 1]))
                    mvwprintw(win, startPrinting->y - 1, startPrinting->x - 1, HALF_RIGHT_VERTICAL_PIPE);
                else
                    mvwprintw(win, startPrinting->y - 1, startPrinting->x - 1, TOP_LEFT_CORNER);
            }
        }
        else if (column != 0 && line != 0)
        {
            if (isAboveUncrossable(maze->cells[line][column]))
            {
                if ((line-1) >= 0 && (column-1) >= 0 &&
                    isLeftUncrossable(maze->cells[line - 1][column]) &&
                    isBelowUncrossable(maze->cells[line - 1][column - 1]))
                    mvwprintw(win, startPrinting->y - 1, startPrinting->x - 1, FULL_VERTICAL_PIPE);
                else if ((line-1) >= 0 && (column-1) >= 0 &&
                         !isLeftUncrossable(maze->cells[line - 1][column]) &&
                         isBelowUncrossable(maze->cells[line - 1][column - 1]))
                    mvwprintw(win, startPrinting->y - 1, startPrinting->x - 1, HALF_BELOW_HORIZONTAL_PIPE);
                else if ((line-1) >= 0 && (column-1) >= 0 &&
                         isLeftUncrossable(maze->cells[line - 1][column]) &&
                         !isBelowUncrossable(maze->cells[line - 1][column - 1]))
                    mvwprintw(win, startPrinting->y - 1, startPrinting->x - 1, HALF_RIGHT_VERTICAL_PIPE);
                else
                    mvwprintw(win, startPrinting->y - 1, startPrinting->x - 1, TOP_LEFT_CORNER);
            }
        }
    }

    if (isAboveUncrossable(maze->cells[line][column]))
    {
        mvwprintw(win, startPrinting->y - 1, startPrinting->x, HORIZONTAL_PIPE);
        if (column != maze->nbCol - 1 && line == 0)
        {
            if (isRightUncrossable(maze->cells[line][column]))
                mvwprintw(win, startPrinting->y - 1, startPrinting->x + 1, HALF_BELOW_HORIZONTAL_PIPE);
            else
                mvwprintw(win, startPrinting->y - 1, startPrinting->x + 1, HORIZONTAL_PIPE);
        }
        if (column != maze->nbCol - 1 && line != 0)
        {
            if (isRightUncrossable(maze->cells[line][column]))
            {
                if ((line - 1) >= 0 && (column+1) < maze->nbCol &&
                    isRightUncrossable(maze->cells[line - 1][column]) &&
                    isAboveUncrossable(maze->cells[line][column + 1]))
                    mvwprintw(win, startPrinting->y - 1, startPrinting->x + 1, FULL_VERTICAL_PIPE);
                else if ((line - 1) >= 0 && (column+1) < maze->nbCol &&
                         !isRightUncrossable(maze->cells[line - 1][column]) &&
                         isAboveUncrossable(maze->cells[line][column + 1]))
                    mvwprintw(win, startPrinting->y - 1, startPrinting->x + 1, HALF_BELOW_HORIZONTAL_PIPE);
                else if ((line - 1) >= 0 && (column+1) < maze->nbCol &&
                         isRightUncrossable(maze->cells[line - 1][column]) &&
                         !isAboveUncrossable(maze->cells[line][column + 1]))
                    mvwprintw(win, startPrinting->y - 1, startPrinting->x + 1, HALF_LEFT_VERTICAL_PIPE);
                else
                    mvwprintw(win, startPrinting->y - 1, startPrinting->x + 1, TOP_RIGHT_CORNER);

            }
            else
            {
                if ((line - 1) >= 0 && (column+1) < maze->nbCol &&
                    isRightUncrossable(maze->cells[line - 1][column]) &&
                    isAboveUncrossable(maze->cells[line][column + 1]))
                    mvwprintw(win, startPrinting->y - 1, startPrinting->x + 1, HALF_ABOVE_HORIZONTAL_PIPE);
                else if ((line - 1) >= 0 && (column+1) < maze->nbCol &&
                         isRightUncrossable(maze->cells[line - 1][column]) &&
                         !isAboveUncrossable(maze->cells[line][column + 1]))
                    mvwprintw(win, startPrinting->y - 1, startPrinting->x + 1, BOTTOM_RIGHT_CORNER);
                else
                    mvwprintw(win, startPrinting->y - 1, startPrinting->x + 1, HORIZONTAL_PIPE);
            }
        }
    }
    if (isRightUncrossable(maze->cells[line][column]))
    {
        mvwprintw(win, startPrinting->y, startPrinting->x + 1, VERTICAL_PIPE);
        if (column == maze->nbCol - 1 && line != maze->nbLine - 1)
        {
            if (isBelowUncrossable(maze->cells[line][column]))
                mvwprintw(win, startPrinting->y + 1, startPrinting->x + 1, HALF_LEFT_VERTICAL_PIPE);
            else
                mvwprintw(win, startPrinting->y + 1, startPrinting->x + 1, VERTICAL_PIPE);
        }
    }
    if (isBelowUncrossable(maze->cells[line][column]))
    {
        mvwprintw(win, startPrinting->y + 1, startPrinting->x, HORIZONTAL_PIPE);
        if (column != maze->nbCol - 1 && line == maze->nbLine - 1)
        {
            if (isRightUncrossable(maze->cells[line][column]))
                mvwprintw(win, startPrinting->y + 1, startPrinting->x + 1, HALF_ABOVE_HORIZONTAL_PIPE);
            else
                mvwprintw(win, startPrinting->y + 1, startPrinting->x + 1, HORIZONTAL_PIPE);
        }
    }

    if (line == 0 && column == 0)
        mvwprintw(win, startPrinting->y - 1, startPrinting->x - 1, TOP_LEFT_CORNER);
    if (line == maze->nbLine - 1 && column == 0)
        mvwprintw(win, startPrinting->y + 1, startPrinting->x - 1, BOTTOM_LEFT_CORNER);
    if (line == 0 && column == maze->nbCol - 1)
        mvwprintw(win, startPrinting->y - 1, startPrinting->x + 1, TOP_RIGHT_CORNER);
    if (line == maze->nbLine - 1 && column == maze->nbCol - 1)
        mvwprintw(win, startPrinting->y + 1, startPrinting->x + 1, BOTTOM_RIGHT_CORNER);

    if (maze->entrypoint.x == column && maze->entrypoint.y == line)
    {
        wattron(win, COLOR_PAIR(2));
        mvwprintw(win, startPrinting->y, startPrinting->x, MAZE_ENTRYPOINT);
        wattron(win, COLOR_PAIR(3));
    }
    if (maze->out.x == column && maze->out.y == line)
    {
        wattron(win, COLOR_PAIR(7));
        mvwprintw(win, startPrinting->y, startPrinting->x, MAZE_OUT);
        wattron(win, COLOR_PAIR(3));
    }
}
