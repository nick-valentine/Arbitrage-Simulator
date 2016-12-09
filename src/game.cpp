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
    unsigned int x = 8, y = 5;
    WorldChunk myChunk[y][x];
    for(unsigned int i = 0; i < y; ++i) {
        for(unsigned int j = 0; j < x; ++j) {
            myChunk[i][j].generateChunk();
        } 
    } 

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

    unsigned int chunkHeight = ConfigLoader::getIntOption("chunk_height");
    unsigned int chunkWidth  = ConfigLoader::getIntOption("chunk_width");
    for(unsigned int i = 0; i < y; ++i) {
        for(unsigned int j = 0; j < x; ++j) {
            myChunk[i][j].draw(i * chunkHeight, j * chunkWidth); 
        } 
    } 
    //myChunk.draw(0, 0);
    
    int c = getch();

    finish(0);
}

static void finish(int sig)
{
    endwin();

    exit(0);
}
