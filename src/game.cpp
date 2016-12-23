#include <curses.h>
#include <iostream>
#include <signal.h>
#include <sstream>
#include <stdlib.h>
#include <stdlib.h>
#include <string>
#include <time.h>

#include "ConfigLoader.hpp"
#include "GameObjects/City.hpp"

#include "Managers/Game.hpp"

static void finish(int sig);
void configure();
void prepareStaticData();

int main()
{
    configure();
    prepareStaticData();
    srand(time(NULL));

    unsigned int chunkHeight = ConfigLoader::getIntOption("chunk_height");
    unsigned int chunkWidth  = ConfigLoader::getIntOption("chunk_width");

    Game myGame;
    myGame.setup();

    int num=0;
    signal(SIGINT, finish);

    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    echo();

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    WorldChunk::setMaxYX(maxY, maxX);

    if(has_colors()) {
        start_color();
    }

    myGame.run();

    finish(0);
}

static void finish(int sig)
{
    endwin();

    exit(0);
}

void configure()
{
    ConfigLoader::load(); 

    std::cout<<"chunk_height: "<<ConfigLoader::getIntOption("chunk_height")<<'\n';
    std::cout<<"chunk_width: "<<ConfigLoader::getIntOption("chunk_width")<<'\n';
    std::cout<<"max_cities_per_chunk: "<<ConfigLoader::getIntOption("max_cities_per_chunk")<<'\n';
    std::cout<<std::endl;
}

void prepareStaticData()
{
    City::load_city_names();
}
