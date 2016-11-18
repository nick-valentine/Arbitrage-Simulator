#ifndef WORLDCHUNK_HPP
#define WORLDCHUNK_HPP

#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "Globals.hpp"
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

private:
    static const std::string SpaceConstant;
    static const std::string CityMarker;
    static const std::string MapMarker;

    enum READ_STATE {
        object = 0,
        map = 1
    };

    static std::map<std::string, void (*)(WorldChunk *self, std::stringstream *ss)> factoryMap; 

    //factory methods
    static void spawnCity(WorldChunk *self, std::stringstream *ss);
    static void spawnTile(WorldChunk *self, std::stringstream *ss);

    std::vector<City> cities;
    std::vector<Tile> tiles;
};


#endif //WORLDCHUNK_HPP
