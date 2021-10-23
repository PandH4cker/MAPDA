#include <stdlib.h>

#include "../includes/utils/bits.h"
#include "../includes/maze/mazeCell.h"

int main(int argc, char ** argv) {
    ncursesInit();
    ncursesInitMouse();
    ncursesInitColors();

    MazeCell aboveWall = 0;
    SET_BIT(aboveWall, 3);

    MazeCell leftWall = 0;
    SET_BIT(leftWall, 2);

    MazeCell belowWall = 0;
    SET_BIT(belowWall, 1);

    MazeCell rightWall = 0;
    SET_BIT(rightWall, 0);

    int choice;
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

        int elt_y,elt_x;
        /*Récupération des coordonnées maximales de la fenêtre*/
        getmaxyx(win,elt_y,elt_x);
        /*Affichage du menu*/
        printMenu(win,elt_y/2 - 20,elt_x/2 - 40);

        /*Création de la box Menu*/
        WINDOW * win_in = NULL;
        win_in = newwin(10,100,elt_y/2,elt_x/2 - 40);
        refresh();
        wrefresh(win);
        box(win_in,0,0);
        wrefresh(win_in);
        /*Récupération du choix*/
        choice = choiceMenu(win_in,win);

        if (choice == 3)
        {
            delwin(win_in);
            delwin(win);
            endwin();
            goto stopN;
        }
    } while (1);
    stopN:
    endwin();
    return EXIT_SUCCESS;
}
