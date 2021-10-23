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
    ncursesInitColors();
    ncursesInitMouse();
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

void printMenu(WINDOW * win,int y,int x)
{
    /**PICROSS ASCII ART**/
    mvwprintw(win,y,x,"    ``         ``....````````````` `                         ` `:::::`````````....:''';;;;;;;;;;,");
    mvwprintw(win,++y,x,"    ###########@@####@#@#######@##@###########################################@@#;::,,,,,::,::,,:");
    mvwprintw(win,++y,x,"    +@,,,,,,,,,,@+,,:#:,,,,,,,,,:;,,,,,,,,,:@@,,,,,,,,,:@@,,,,,,,,,,@#,,,,,,,,,,@;:,```````````,:");
    mvwprintw(win,++y,x,"    +@          ,#  ,+          :;          ';          +:          @,         `@;:,` ` ``` ` `::");
    mvwprintw(win,++y,x,"    +@      `   ,#  :+          ;;  ``````  ':  ``` ``  +,  ````````#,  ````````@;:,``,,:,:,,.`::");
    mvwprintw(win,++y,x,"    +@  :####+  :#  :+  ;#######+;  ;####;  ':` +####:` +:  +#######@:  #########;:,``,:,,,:,``::");
    mvwprintw(win,++y,x,"    +@  ::::::``:#  ;+ `;########;  ::,::: `;;  #,:,,:``+:``,,:::::;#,  :::::::'#;:,``,,,,,,,``::");
    mvwprintw(win,++y,x,"    +@ `````````:# `;+``;########;``````` ``';` #,,,,:``+: ````````.#:``````````@;::` ``.`` ` `,:");
    mvwprintw(win,++y,x,"    +@ `````````'# `;+``;########;``` ``` `.#;` #,::,:``+'.`````````#;`````````.@;;,````.``````::");
    mvwprintw(win,++y,x,"    +#``;######### `;+``;#######@;``+##;``'@#;``+;:::;``+########:``#########:`.@;:,``,::,::,::::");
    mvwprintw(win,++y,x,"    +#``;#########``;+``:;::::;:''``'@#'``::''``;;:;::``+;::::::;:``#:::::::::`.@;:,``,:,,:,:::::");
    mvwprintw(win,++y,x,"    +#``;#########``;+````````.`''``+##'````';``````````+;`````````.#;`````````.@;:,```````````,: ");
    mvwprintw(win,++y,x,"    +#``;#########``;@.`````````''``+###````++.````````,@;`````````:#;`````````:@:;,```````````:: ");
    mvwprintw(win,++y,x,"    +#@@##########@###@##@#########@##@#@@#@##@@##@@###@###@#@#@#@#@###@@@@@@@@@+`:::,:,::::::::: ");
    mvwprintw(win,++y,x,"    +''''''''''';'''''''''''''''''''''''''''''''''''''''''''''''''';''''''''''';..;,,,,,,,,,,,,,; ");
/**END ART**/
}

/*Affichage sur une fenêtre un menu et retourne le choix de l'utilisateur*/
int choiceMenu(WINDOW * win_in, WINDOW * win)
{
    /**Box MENU**/
    int elt_y1,elt_x1;
    getmaxyx(win_in,elt_y1,elt_x1); // Récupère les coordonées maximales de la fenêtre
    wattron(win_in,A_BOLD); // Attribution type gras au texte
    mvwprintw(win_in,0,elt_x1/2 - 5,"###MENU###");
    wattroff(win_in,A_BOLD); // Désattribution
    wrefresh(win_in);
    keypad(win_in,TRUE); // Activation des touches
    int i,highlight = 0,choice;
/*Initialisation du menu*/
    char choices[3][15] = {"» Aléatoire",
                           "» Fichier",
                           "» Quitter"};
    while(true)
    {
        for(i = 0; i < 3; i++)
        {
            /* Si on est sur le highlight */
            if(i == highlight)
                wattron(win_in,A_REVERSE); // On surligne le texte
            mvwprintw(win_in,elt_y1/2 - 1 + i,1,"%s",choices[i]); // Affichage en ligne des choix
            wattroff(win_in,A_REVERSE); // Désattribution

        }
        choice = wgetch(win_in); // On récupère le choix
        mvwprintw(win_in, 10, 10, "choice = %d", choice);
        switch(choice)
        {
            /*Si on appuie fleche haut*/
            case KEY_UP:
                /*On joue un son*/
                //system("play -q soundtrack/beep-07.mp3 &");
                highlight--;
                /* Replacement de l'highlight si on sort du tableau */
                if(highlight == -1) highlight = 2;
                break;
                /*Si on appuie fleche bas*/
            case KEY_DOWN:
                /*On joue un son*/
                //system("play -q soundtrack/beep-07.mp3 &");
                highlight++;
                /* Replacement de l'highlight si on sort du tableau */
                if(highlight == 3) highlight = 0;
                break;
                /*Par défaut on ne fait rien*/
            default:
                break;
        }
        /**10 is the numerical representation for LF (LineFeed / '/n')**/
        if(choice == 10)
        {
            return highlight; //Retourne le choix
        }
    }
/**END Box MENU**/
}