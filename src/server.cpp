#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>

#include "ConfigLoader.hpp"
#include "GameObjects/City.hpp"
#include "GameObjects/WorldChunk.hpp"
#include "WorldGen/NoiseFunc.hpp"

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
    myChunk.generateChunk(0, 0);
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

    NoiseFunc myNoise(10.0);
    for(int i = 0; i < 10; ++i) {
        for( int j = 0; j < 10; ++j) {
            std::cout<<myNoise.get(i, j)<<"\t";
        }
        std::cout<<"\n";
    }

    std::stringstream noiseSS, noise2SS;
    myNoise.toStringStream(&noiseSS);
    std::cout<<noiseSS.str()<<std::endl;
    NoiseFunc noise2(&noiseSS);
    noise2.toStringStream(&noise2SS);
    std::cout<<(bool)(noiseSS.str() == noise2SS.str())<<std::endl;

    return 0;
}
