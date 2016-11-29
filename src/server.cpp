#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>

#include "GameObjects/WorldChunk.hpp"

int main()
{

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
