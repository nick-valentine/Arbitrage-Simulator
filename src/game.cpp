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
#include "WorldGen/NoiseFunc.hpp"
#include "GameObjects/World.hpp"

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

    unsigned int chunkHeight = ConfigLoader::getIntOption("chunk_height");
    unsigned int chunkWidth  = ConfigLoader::getIntOption("chunk_width");

    World myWorld("testWorld");

    myWorld.generateWorld();

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

    myWorld.draw(0, 0);
    
    int c = getch();

    finish(0);
}

static void finish(int sig)
{
    endwin();

    exit(0);
}
