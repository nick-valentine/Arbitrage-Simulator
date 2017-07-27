#include <curses.h>
#include <iostream>
#include <signal.h>
#include <sstream>
#include <stdlib.h>
#include <stdlib.h>
#include <string>
#include <time.h>

#include "Managers/Game.hpp"
 
static void finish(int sig);

int main()
{
    srand(time(NULL));

    int num=0;
    signal(SIGINT, finish);

    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    echo();

    if(has_colors()) {
        start_color();
    }

    Game myGame;
    myGame.setup();
    myGame.run();

    finish(0);
}

static void finish(int sig)
{
    endwin();

    exit(0);
}

