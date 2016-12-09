#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>

#include "ConfigLoader.hpp"
#include "GameObjects/City.hpp"
#include "GameObjects/WorldChunk.hpp"

static void finish(int sig);

void configure()
{
    ConfigLoader::load(); 
    std::cout<<"chunk_height: "<<ConfigLoader::getIntOption("chunk_height")<<'\n';
    std::cout<<"chunk_width: "<<ConfigLoader::getIntOption("chunk_width")<<'\n';
    std::cout<<"max_cities_per_chunk: "<<ConfigLoader::getIntOption("max_cities_per_chunk")<<'\n';
    std::cout<<std::endl;
}

int main()
{
    configure();
    City::load_city_names();
    srand(time(NULL));
    WorldChunk myChunk;
    myChunk.generateChunk();

    int num=0;
    (void) signal(SIGINT, finish);

    (void) initscr();
    keypad(stdscr, TRUE);
    (void) cbreak();
    (void) echo();

    if(has_colors()) {
        start_color();

        init_pair(1, COLOR_RED,     COLOR_BLACK);
        init_pair(2, COLOR_GREEN,   COLOR_BLACK);
        init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(4, COLOR_BLUE,    COLOR_BLACK);
        init_pair(5, COLOR_CYAN,    COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_WHITE,   COLOR_BLACK);
    }

    myChunk.draw(0, 0);
    
    int c = getch();

    finish(0);
}

static void finish(int sig)
{
    endwin();

    exit(0);
}
