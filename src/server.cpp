#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>

#include "ConfigLoader.hpp"
#include "GameObjects/WorldChunk.hpp"

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

    srand(time(NULL));
    WorldChunk myChunk;
    myChunk.generateChunk();
    std::stringstream oss;
    myChunk.toStringStream(&oss);
    std::cout<<oss.str()<<std::endl;
//    std::string gameData = "city Hamlet, 1, 1\nMAP\n1 2 3 1 2 2 1 1 1 2 2 3 1 1 2 3 1 1 2 3 1 1 1 2 1 1 1 1";
//    std::stringstream iss;
//    iss.str(gameData);
//    WorldChunk myChunk(&iss);
//
//    std::stringstream oss;
//    myChunk.toStringStream(&oss);
//    std::cout<<gameData<<std::endl;
//    std::cout<<oss.str()<<std::endl;

    return 0;
}
