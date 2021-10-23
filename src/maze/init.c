//
// Created by drayr on 23/10/2021.
//

#include <stdlib.h>

#include "../../includes/maze/init.h"

void ncursesInitColors()
{
    if (has_colors() == FALSE)
    {
        endwin();
        fprintf(stderr, "The terminal does not support colors.\n");
        exit(EXIT_FAILURE);
    }

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(5, COLOR_BLUE,  COLOR_BLACK);
    init_pair(6, COLOR_YELLOW,COLOR_BLACK);
}

void ncursesInit()
{
    initscr();	        /* Démarre le mode ncurses */
    cbreak();	        /* Pour les saisies clavier (desac. mise en buffer) */
    noecho();             /* Désactive l'affichage des caractères saisis */
    keypad(stdscr, TRUE);	/* Active les touches spécifiques */
    refresh();            /* Met a jour l'affichage */
    curs_set(FALSE);      /* Masque le curseur */
}

void ncursesInitMouse()
{
    if(!mousemask(ALL_MOUSE_EVENTS, NULL))
    {
        endwin();
        fprintf(stderr, "Error while mouse initialization.\n");
        exit(EXIT_FAILURE);
    }
    if(has_mouse() != TRUE)
    {
        endwin();
        fprintf(stderr, "No mouse detected.\n");
        exit(EXIT_FAILURE);
    }
}