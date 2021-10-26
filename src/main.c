#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "../includes/maze/maze.h"
#include "../includes/pathfinding/pathfinding.h"


int main(int argc, char ** argv) {
    setlocale(LC_ALL, "");
    srand(time(NULL));

    Maze m;
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s [-f <filename> | -r <width> <height>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (strcmp(argv[1], "-f") == 0)
        m = fromFile(argv[2]);
    else if (strcmp(argv[1], "-r") == 0 && argc < 5)
        m = randomMaze(atoi(argv[2]), atoi(argv[3]));
    else
    {
        fprintf(stderr, "Usage: %s [-f <filename> | -r <width> <height>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    puts("Loaded a Maze:");
    printf("\tWidth: %d\n", m.nbCol);
    printf("\tHeight: %d\n", m.nbLine);
    printf("\tEntrypoint at (%d, %d)\n", m.entrypoint.x, m.entrypoint.y);
    printf("\tOut at (%d, %d)\n", m.out.x, m.out.y);

    for (int i = 0; i < m.nbLine; ++i)
    {
        for (int j = 0; j < m.nbCol; ++j)
            printf("%2d ", m.cells[i][j].cellValue);
        puts("");
    }
    m.resolver = m.entrypoint;

    ncursesInit();
    int choice;
    int status;
    do
    {
        clear();
        int width, height, startX, startY;
        getmaxyx(stdscr, height, width);
        startX = startY = 0;

        WINDOW * win = NULL;
        win = newwin(height, width, startY, startX);
        refresh();
        char c = '#';
        box(win , (int)c, (int)c);
        wrefresh(win);
        wbkgd(win, COLOR_PAIR(3));

        int eltX, eltY;
        getmaxyx(win, eltY, eltX);
        int middleX = 5, middleY = 5;

        printMaze(win, (Position){
            .x = 5,
            .y = 5
        }, m);

        status = findPath(&m);

        wtimeout(win, 100);
        choice = wgetch(win);
    } while (choice != 'q');
    endwin();

    for (int i = 0; i < m.nbLine; ++i) free(m.cells[i]);
    free(m.cells);
    m.cells = NULL;
    return EXIT_SUCCESS;
    /*int choice;
    do
    {
        int width, height, startY, startX;
        getmaxyx(stdscr, height, width);
        startX = startY = 0;

        WINDOW * win = NULL;
        win = newwin(height, width, startY, startX);
        refresh();
        char c = '#';
        box(win, (int)c, (int)c);
        wrefresh(win);
        wbkgd(win, COLOR_PAIR(3));

        int elt_y,elt_x;*/
        /*Récupération des coordonnées maximales de la fenêtre*/
        /*getmaxyx(win,elt_y,elt_x);*/
        /*Affichage du menu*/
        /*printMenu(win,elt_y/2 - 20,elt_x/2 - 40);*/

        /*Création de la box Menu*/
        /*WINDOW * win_in = NULL;
        win_in = newwin(10,100,elt_y/2,elt_x/2 - 40);
        refresh();
        wrefresh(win);
        box(win_in,0,0);
        wrefresh(win_in);*/
        /*Récupération du choix*/
        /*choice = choiceMenu(win_in,win);
        switch (choice) {
            case 0:
                clear();



                delwin(win_in);
                delwin(win);
                endwin();
                break;
            case 2:
                delwin(win_in);
                delwin(win);
                endwin();
                break;
        }
    } while (choice != 2);*/
}
