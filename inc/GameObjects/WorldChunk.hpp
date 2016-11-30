#ifndef WORLDCHUNK_HPP
#define WORLDCHUNK_HPP

#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>

#include "Globals.hpp"
#include "ConfigLoader.hpp"
#include "GameObjects/AbstractGameObject.hpp"
#include "GameObjects/City.hpp"
#include "GameObjects/Tile.hpp"

class WorldChunk : public AbstractGameObject
{
public:
    WorldChunk();
    WorldChunk(std::stringstream *ss);

    /**
     * The stringstream structure expected into this is
     * ObjectName objectData1, objectData2, ...
     * ObjectName objectData1, objectData2, ...
     * MAP
     * 1 2 3 4 2 3 1 2 3  1 ...
     */
    void fromStringStream(std::stringstream *ss);
    void toStringStream(std::stringstream *ss);

    void generateChunk();
private:
    static const std::string SpaceConstant;
    static const std::string CityMarker;
    static const std::string MapMarker;

    static bool configured;
    static unsigned int chunk_height;
    static unsigned int chunk_width;
    static int max_cities_per_chunk;

    enum READ_STATE {
        object = 0,
        map = 1
    };

    static std::map<std::string, void (*)(WorldChunk *self, std::stringstream *ss)> factoryMap; 

    //factory methods
    static void spawnCity(WorldChunk *self, std::stringstream *ss);

    void configure();

    void organizeTiles(std::vector<Tile> tiles);

    std::vector<City> cities;
    std::vector< std::vector<Tile> > tiles;
};


#endif //WORLDCHUNK_HPP