#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <curses.h>
#include <vector>

#include "GameObjects/AbstractGameObject.hpp"
#include "ColorPallete.hpp"

class Tile : public AbstractGameObject
{
public:
    Tile();
    Tile(int type, int elevation);
    Tile(std::stringstream *ss);
    static Tile randomSpawn(float tileInput = -1.0, float elevationInput = -1.0);
    void fromStringStream(std::stringstream *ss);
    void toStringStream(std::stringstream *ss);

    //generalized tiles that may be spawned randomly
    enum TileLookup
    {
        PLAINS = 0,
        MOUNTAINS = 1,
        WATER = 2,
        SWAMPS = 3,
        HILLS = 5,
        DESERTS = 6,
        FORESTS = 7
    };

    //specialized tiles that must be set
    enum TilesReserved
    {
        CITIES = 4
    };

    static void setPallete();

    bool convertToCity();
    void draw();

private:
    static void init();

    static const int veryLargeMultiplyer = 1000000;
    static const int elevationMax = 128;
    static const int TypeCount = 8;
    static const int allowedSpawnCount = 7;
    static const int allowedCityCount = 5;
    // @todo: add colors etc.
    struct TileType
    {
        char tile;
        unsigned int colorPair;
        unsigned int elevationMin;
        unsigned int elevationMax;

        TileType(
            char tile, 
            unsigned int colorPair,
            unsigned int elevationMin,
            unsigned int elevationMax
        ) : tile(tile), 
            colorPair(colorPair),
            elevationMin(elevationMin),
            elevationMax(elevationMax)
        {}
    };

    static const int AllowedSpawns[allowedSpawnCount];
    static const int TilesWhichMayHaveCities[allowedCityCount];
    static const TileType Tiles[TypeCount]; 

    static ColorPallete tilePallete;
    static bool colorPalleteInitialized;

    //index into Tiles 
    int myType;
    int myElevation;
};

#endif //TILE_HPP
