//
// Created by drayr on 23/10/2021.
//

#include <stdlib.h>

#include "../../includes/maze/maze.h"

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
        printf("%d %d\n", nbLine, nbCol);
        Maze maze;
        maze.entrypoint = entrypoint;
        maze.out = out;
        maze.nbLine = nbLine;
        maze.nbCol = nbCol;

        maze.cells = calloc(maze.nbLine, sizeof(MazeCell*));
        for (int i = 0; i < maze.nbLine; ++i) maze.cells[i] = calloc(maze.nbCol, sizeof (MazeCell));

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
            if (isLeftUncrossable(m.cells[i][j]))
            {
                mvwprintw(win,startPrinting.y,startPrinting.x - 1, VERTICAL_PIPE);
                if (j == 0 && i != m.nbLine - 1) // Left border
                {
                    if (isBelowUncrossable(m.cells[i][j]))
                        mvwprintw(win,startPrinting.y + 1,startPrinting.x - 1, HALF_RIGHT_VERTICAL_PIPE);
                    else
                        mvwprintw(win,startPrinting.y + 1,startPrinting.x - 1, VERTICAL_PIPE);
                }
                else if (j != 0 && i != m.nbLine - 1) // Inside border
                {
                    if (isBelowUncrossable(m.cells[i][j]))
                    {
                        if ((i+1) < m.nbLine && (j-1) >= 0 &&
                            isBelowUncrossable(m.cells[i][j - 1]) &&
                            isLeftUncrossable(m.cells[i + 1][j]))
                            mvwprintw(win,startPrinting.y + 1,startPrinting.x - 1, FULL_VERTICAL_PIPE);
                        else if ((i+1) < m.nbLine && (j-1) >= 0 &&
                                 !isBelowUncrossable(m.cells[i][j - 1]) &&
                                 isLeftUncrossable(m.cells[i + 1][j]))
                            mvwprintw(win,startPrinting.y + 1,startPrinting.x - 1, HALF_RIGHT_VERTICAL_PIPE);
                        else if ((i+1) < m.nbLine && (j-1) >= 0 &&
                                 isBelowUncrossable(m.cells[i][j - 1]) &&
                                 !isLeftUncrossable(m.cells[i + 1][j]))
                            mvwprintw(win,startPrinting.y + 1,startPrinting.x - 1, HALF_ABOVE_HORIZONTAL_PIPE);
                        else
                            mvwprintw(win,startPrinting.y + 1,startPrinting.x - 1, BOTTOM_LEFT_CORNER);
                    }
                    else
                    {
                        if ((i+1) < m.nbLine && (j-1) >= 0 &&
                            isBelowUncrossable(m.cells[i][j - 1]) &&
                            isLeftUncrossable(m.cells[i + 1][j]))
                            mvwprintw(win,startPrinting.y + 1,startPrinting.x - 1, HALF_LEFT_VERTICAL_PIPE);
                        else if ((i+1) < m.nbLine && (j-1) >= 0 &&
                                 isBelowUncrossable(m.cells[i][j - 1]) &&
                                 !isLeftUncrossable(m.cells[i + 1][j]))
                            mvwprintw(win,startPrinting.y + 1,startPrinting.x - 1, BOTTOM_RIGHT_CORNER);
                        else
                            mvwprintw(win,startPrinting.y + 1,startPrinting.x - 1, VERTICAL_PIPE);
                    }

                    if (isAboveUncrossable(m.cells[i][j]) && i != 0)
                    {
                        if ((i-1) >= 0 && (j-1) >= 0 &&
                            isLeftUncrossable(m.cells[i - 1][j]) &&
                            isBelowUncrossable(m.cells[i - 1][j - 1]))
                            mvwprintw(win,startPrinting.y - 1,startPrinting.x - 1, FULL_VERTICAL_PIPE);
                        else if ((i-1) >= 0 && (j-1) >= 0 &&
                                 !isLeftUncrossable(m.cells[i - 1][j]) &&
                                 isBelowUncrossable(m.cells[i - 1][j - 1]))
                            mvwprintw(win,startPrinting.y - 1,startPrinting.x - 1, HALF_BELOW_HORIZONTAL_PIPE);
                        else if ((i-1) >= 0 && (j-1) >= 0 &&
                                 isLeftUncrossable(m.cells[i - 1][j]) &&
                                 !isBelowUncrossable(m.cells[i - 1][j - 1]))
                            mvwprintw(win,startPrinting.y - 1,startPrinting.x - 1, HALF_RIGHT_VERTICAL_PIPE);
                        else
                            mvwprintw(win,startPrinting.y - 1,startPrinting.x - 1, TOP_LEFT_CORNER);
                    }
                }
            }

            if (isAboveUncrossable(m.cells[i][j]))
            {
                mvwprintw(win,startPrinting.y - 1,startPrinting.x, HORIZONTAL_PIPE);
                if (j != m.nbCol - 1 && i == 0)
                {
                    if (isRightUncrossable(m.cells[i][j]))
                        mvwprintw(win,startPrinting.y - 1,startPrinting.x + 1, HALF_BELOW_HORIZONTAL_PIPE);
                    else
                        mvwprintw(win,startPrinting.y - 1,startPrinting.x + 1, HORIZONTAL_PIPE);
                }
                if (j != m.nbCol - 1 && i != 0)
                {
                    if (isRightUncrossable(m.cells[i][j]))
                    {
                        if ((i - 1) >= 0 && (j+1) < m.nbCol &&
                            isRightUncrossable(m.cells[i - 1][j]) &&
                            isAboveUncrossable(m.cells[i][j + 1]))
                            mvwprintw(win,startPrinting.y - 1,startPrinting.x + 1, FULL_VERTICAL_PIPE);
                        else if ((i - 1) >= 0 && (j+1) < m.nbCol &&
                                 !isRightUncrossable(m.cells[i - 1][j]) &&
                                 isAboveUncrossable(m.cells[i][j + 1]))
                            mvwprintw(win,startPrinting.y - 1,startPrinting.x + 1, HALF_BELOW_HORIZONTAL_PIPE);
                        else if ((i - 1) >= 0 && (j+1) < m.nbCol &&
                                 isRightUncrossable(m.cells[i - 1][j]) &&
                                 !isAboveUncrossable(m.cells[i][j + 1]))
                            mvwprintw(win,startPrinting.y - 1,startPrinting.x + 1, HALF_LEFT_VERTICAL_PIPE);
                        else
                            mvwprintw(win,startPrinting.y - 1,startPrinting.x + 1, TOP_RIGHT_CORNER);

                    }
                    else
                    {
                        if ((i - 1) >= 0 && (j+1) < m.nbCol &&
                            isRightUncrossable(m.cells[i - 1][j]) &&
                            isAboveUncrossable(m.cells[i][j + 1]))
                            mvwprintw(win,startPrinting.y - 1,startPrinting.x + 1, HALF_ABOVE_HORIZONTAL_PIPE);
                        else if ((i - 1) >= 0 && (j+1) < m.nbCol &&
                                 isRightUncrossable(m.cells[i - 1][j]) &&
                                 !isAboveUncrossable(m.cells[i][j + 1]))
                            mvwprintw(win,startPrinting.y - 1,startPrinting.x + 1, BOTTOM_RIGHT_CORNER);
                        else
                            mvwprintw(win,startPrinting.y - 1,startPrinting.x + 1, HORIZONTAL_PIPE);
                    }
                }
            }
            if (isRightUncrossable(m.cells[i][j]))
            {
                mvwprintw(win,startPrinting.y,startPrinting.x + 1, VERTICAL_PIPE);
                if (j == m.nbCol - 1 && i != m.nbLine - 1)
                {
                    if (isBelowUncrossable(m.cells[i][j]))
                        mvwprintw(win,startPrinting.y + 1,startPrinting.x + 1, HALF_LEFT_VERTICAL_PIPE);
                    else
                        mvwprintw(win,startPrinting.y + 1,startPrinting.x + 1, VERTICAL_PIPE);
                }
            }
            if (isBelowUncrossable(m.cells[i][j]))
            {
                mvwprintw(win,startPrinting.y + 1,startPrinting.x, HORIZONTAL_PIPE);
                if (j != m.nbCol - 1 && i == m.nbLine - 1)
                {
                    if (isRightUncrossable(m.cells[i][j]))
                        mvwprintw(win,startPrinting.y + 1,startPrinting.x + 1, HALF_ABOVE_HORIZONTAL_PIPE);
                    else
                        mvwprintw(win,startPrinting.y + 1,startPrinting.x + 1, HORIZONTAL_PIPE);
                }
            }

            if (i == 0 && j == 0)
                mvwprintw(win, startPrinting.y - 1, startPrinting.x - 1, TOP_LEFT_CORNER);
            if (i == m.nbLine - 1 && j == 0)
                mvwprintw(win, startPrinting.y + 1, startPrinting.x - 1, BOTTOM_LEFT_CORNER);
            if (i == 0 && j == m.nbCol - 1)
                mvwprintw(win, startPrinting.y - 1, startPrinting.x + 1, TOP_RIGHT_CORNER);
            if (i == m.nbLine - 1 && j == m.nbCol - 1)
                mvwprintw(win, startPrinting.y + 1, startPrinting.x + 1, BOTTOM_RIGHT_CORNER);

            if (m.entrypoint.x == j && m.entrypoint.y == i)
                mvwprintw(win, startPrinting.y, startPrinting.x, MAZE_ENTRYPOINT);
            if (m.out.x == j && m.out.y == i)
                mvwprintw(win, startPrinting.y, startPrinting.x, MAZE_OUT);
            startPrinting.x += 2;
        }
        startPrinting.x = 5;
        startPrinting.y += 2;
    }
}