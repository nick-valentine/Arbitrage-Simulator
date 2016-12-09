#ifndef TILE_HPP
#define TILE_HPP

#include <stdlib.h>
#include <sstream>
#include <string>
#include <curses.h>

#include "GameObjects/AbstractGameObject.hpp"

class Tile : public AbstractGameObject
{
public:
    Tile();
    Tile(int type);
    Tile(std::stringstream *ss);
    static Tile randomSpawn();
    void fromStringStream(std::stringstream *ss);
    void toStringStream(std::stringstream *ss);

    //generalized tiles that may be spawned randomly
    enum TileLookup
    {
        PLAINS = 0,
        MOUNTAINS = 1,
        WATER = 2,
        SWAMPS = 3
    };

    //specialized tiles that must be set
    enum TilesReserved
    {
        CITIES = 4
    };

    void draw();

private:
    static const int TypeCount = 5;
    static const int allowedSpawnCount = 4;
    // @todo: add colors etc.
    struct TileType
    {
        char tile;

        TileType(char tile) : tile(tile) {}
    };

    static const int AllowedSpawns[allowedSpawnCount];
    static const TileType Tiles[TypeCount]; 

    //index into Tiles 
    int myType;
};

#endif //TILE_HPP
