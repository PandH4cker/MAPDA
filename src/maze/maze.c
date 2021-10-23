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