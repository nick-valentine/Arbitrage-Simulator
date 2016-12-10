#ifndef TILE_HPP
#define TILE_HPP

#include <stdlib.h>
#include <sstream>
#include <string>
#include <curses.h>

#include "GameObjects/AbstractGameObject.hpp"
#include "ColorPallete.hpp"

class Tile : public AbstractGameObject
{
public:
    Tile();
    Tile(int type);
    Tile(std::stringstream *ss);
    static Tile randomSpawn(float randInput = -1.0);
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

    static void setPallete();
    void draw();

private:
    static void init();

    static const int veryLargeMultiplyer = 1000000;
    static const int TypeCount = 5;
    static const int allowedSpawnCount = 4;
    // @todo: add colors etc.
    struct TileType
    {
        char tile;
        unsigned int colorPair;

        TileType(char tile, unsigned int colorPair) : tile(tile), colorPair(colorPair) {}
    };

    static const int AllowedSpawns[allowedSpawnCount];
    static const TileType Tiles[TypeCount]; 

    static ColorPallete tilePallete;
    static bool colorPalleteInitialized;

    //index into Tiles 
    int myType;
};

#endif //TILE_HPP
