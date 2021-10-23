#include <stdlib.h>
#include <locale.h>

#include "../includes/maze/maze.h"

int main(int argc, char ** argv) {
    setlocale(LC_ALL, "");

    Maze m = fromFile("../ExampleMaze");

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

    ncursesInit();
    int choice;
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

        for (int i = 0; i < m.nbLine; ++i)
        {
            for (int j = 0; j < m.nbCol; ++j)
            {
                if (isLeftUncrossable(m.cells[i][j]))
                {
                    mvwprintw(win,middleY,middleX - 1, "║");
                    if (j == 0 && i != m.nbLine - 1)
                    {
                        if (isBelowUncrossable(m.cells[i][j]))
                            mvwprintw(win,middleY + 1,middleX - 1, "╠");
                        else
                            mvwprintw(win,middleY + 1,middleX - 1, "║");
                    }
                    else if (j != 0 && i != m.nbLine - 1)
                    {
                        if (isBelowUncrossable(m.cells[i][j]))
                        {
                            if ((i+1) < m.nbLine && (j-1) >= 0 &&
                                isBelowUncrossable(m.cells[i][j - 1]) &&
                                isLeftUncrossable(m.cells[i + 1][j]))
                                mvwprintw(win,middleY + 1,middleX - 1, "╬");
                            else if ((i+1) < m.nbLine && (j-1) >= 0 &&
                                     !isBelowUncrossable(m.cells[i][j - 1]) &&
                                     isLeftUncrossable(m.cells[i + 1][j]))
                                mvwprintw(win,middleY + 1,middleX - 1, "╠");
                            else if ((i+1) < m.nbLine && (j-1) >= 0 &&
                                     isBelowUncrossable(m.cells[i][j - 1]) &&
                                     !isLeftUncrossable(m.cells[i + 1][j]))
                                mvwprintw(win,middleY + 1,middleX - 1, "╩");
                            else
                                mvwprintw(win,middleY + 1,middleX - 1, "╚");
                        }
                        else
                        {
                            if ((i+1) < m.nbLine && (j-1) >= 0 &&
                                isBelowUncrossable(m.cells[i][j - 1]) &&
                                isLeftUncrossable(m.cells[i + 1][j]))
                                mvwprintw(win,middleY + 1,middleX - 1, "╣");
                            else if ((i+1) < m.nbLine && (j-1) >= 0 &&
                                     isBelowUncrossable(m.cells[i][j - 1]) &&
                                     !isLeftUncrossable(m.cells[i + 1][j]))
                                mvwprintw(win,middleY + 1,middleX - 1, "╝");
                            else
                                mvwprintw(win,middleY + 1,middleX - 1, "║");
                        }
                    }
                }

                if (isAboveUncrossable(m.cells[i][j]))
                {
                    mvwprintw(win,middleY - 1,middleX, "═");
                    if (j != m.nbCol - 1 && i == 0)
                    {
                        if (isRightUncrossable(m.cells[i][j]))
                            mvwprintw(win,middleY - 1,middleX + 1, "╦");
                        else
                            mvwprintw(win,middleY - 1,middleX + 1, "═");
                    }
                    if (j != m.nbCol - 1 && i != 0)
                    {
                        if (isRightUncrossable(m.cells[i][j]))
                        {
                            if ((i - 1) >= 0 && (j+1) < m.nbCol &&
                                isRightUncrossable(m.cells[i - 1][j]) &&
                                isAboveUncrossable(m.cells[i][j + 1]))
                                mvwprintw(win,middleY - 1,middleX + 1, "╬");
                            else if ((i - 1) >= 0 && (j+1) < m.nbCol &&
                                !isRightUncrossable(m.cells[i - 1][j]) &&
                                isAboveUncrossable(m.cells[i][j + 1]))
                                mvwprintw(win,middleY - 1,middleX + 1, "╦");//╦
                            else if ((i - 1) >= 0 && (j+1) < m.nbCol &&
                                isRightUncrossable(m.cells[i - 1][j]) &&
                                !isAboveUncrossable(m.cells[i][j + 1]))
                                mvwprintw(win,middleY - 1,middleX + 1, "╣");
                            else
                                mvwprintw(win,middleY - 1,middleX + 1, "╗");//╗

                        }
                        else
                        {
                            if ((i - 1) >= 0 && (j+1) < m.nbCol &&
                                isRightUncrossable(m.cells[i - 1][j]) &&
                                isAboveUncrossable(m.cells[i][j + 1]))
                                mvwprintw(win,middleY - 1,middleX + 1, "╩");
                            else if ((i - 1) >= 0 && (j+1) < m.nbCol &&
                                isRightUncrossable(m.cells[i - 1][j]) &&
                                !isAboveUncrossable(m.cells[i][j + 1]))
                                mvwprintw(win,middleY - 1,middleX + 1, "╝");
                            else
                                mvwprintw(win,middleY - 1,middleX + 1, "═");
                        }
                    }
                }
                if (isRightUncrossable(m.cells[i][j]))
                {
                    mvwprintw(win,middleY,middleX + 1, "║");
                    if (j == m.nbCol - 1 && i != m.nbLine - 1)
                    {
                        if (isBelowUncrossable(m.cells[i][j]))
                            mvwprintw(win,middleY + 1,middleX + 1, "╣");
                        else
                            mvwprintw(win,middleY + 1,middleX + 1, "║");
                    }
                }
                if (isBelowUncrossable(m.cells[i][j]))
                {
                    mvwprintw(win,middleY + 1,middleX, "═");
                    if (j != m.nbCol - 1 && i == m.nbLine - 1)
                    {
                        if (isRightUncrossable(m.cells[i][j]))
                            mvwprintw(win,middleY + 1,middleX + 1, "╩");
                        else
                            mvwprintw(win,middleY + 1,middleX + 1, "═");
                    }
                }

                if (i == 0 && j == 0)
                    mvwprintw(win, middleY - 1, middleX - 1, "╔");
                if (i == m.nbLine - 1 && j == 0)
                    mvwprintw(win, middleY + 1, middleX - 1, "╚");
                if (i == 0 && j == m.nbCol - 1)
                    mvwprintw(win, middleY - 1, middleX + 1, "╗");
                if (i == m.nbLine - 1 && j == m.nbCol - 1)
                    mvwprintw(win, middleY + 1, middleX + 1, "╝");

                if (m.entrypoint.x == j && m.entrypoint.y == i)
                    mvwprintw(win, middleY, middleX, "E");
                if (m.out.x == j && m.out.y == i)
                    mvwprintw(win, middleY, middleX, "S");
                middleX += 2;
            }
            middleX = 5;
            middleY += 2;
        }
        choice = wgetch(win);
    } while (choice != 'q');


    for (int i = 0; i < m.nbLine; ++i) free(m.cells[i]);
    free(m.cells);
    m.cells = NULL;
    endwin();
    /*ncursesInit();
    ncursesInitMouse();
    ncursesInitColors();*/

    /*MazeCell aboveWall = 0;
    SET_BIT(aboveWall, 3);

    MazeCell leftWall = 0;
    SET_BIT(leftWall, 2);

    MazeCell belowWall = 0;
    SET_BIT(belowWall, 1);

    MazeCell rightWall = 0;
    SET_BIT(rightWall, 0);*/

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
    return EXIT_SUCCESS;
}
