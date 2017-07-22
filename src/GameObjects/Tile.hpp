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
#include "Window/Window.hpp"

/**
 * Tile.
 * A flyweight style class for managing each world unit. To the end user, these
 * appear as simple characters on a screen representing a mountain, or a
 * forest.
 */
class Tile : public AbstractGameObject
{
public:
    Tile();
    Tile(int type, int elevation);
    Tile(std::stringstream *ss);

    /**
     * Random Spawn.
     * Factory function which can take a bias and an elevation, then returns a
     * tile allowed at that elevation, with the random choosing biased.
     *
     * @param  float tileInput bias for the random function
     * @param  float elevationInput elevation that this tile is to spawn at
     */
    static Tile randomSpawn(float tileInput = -1.0, float elevationInput = -1.0);
    void fromStringStream(std::stringstream *ss);
    void toStringStream(std::stringstream *ss);

    /**
     * Tile Lookup.
     * Generalized tiles that may be spawned randomly
     */
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

    /**
     * Reserved Tiles.
     * Specialized tiles that must be set.
     */
    enum TilesReserved
    {
        CITIES = 4
    };

    /**
     * Set Pallete.
     * Set the color pallete for all tiles to be the current one.
     */
    static void setPallete();

    /**
     * Convert this tile to a city tile if this tile may contain a city.
     *
     * @return bool If this tile was converted to a city.
     */
    bool convertToCity();

    /**
     * Check if this tile may be converted to a city
     *
     * @return bool If this tile can be converted to a city.
     */
    bool canConvertToCity();

    int getLivability();

    /**
     * Draw this tile.
     *
     * @param  Window::window_ptr window buffer to draw the tile on to
     * @param  int top Y coordinate to draw the tile on
     * @param  int left X coordinate to draw the tile on
     * @param  bool cull if the player has never seen this tile, do not draw
     *                      it, If the player has seen this tile, draw it in
     *                      greyscale.
     */
    void drawAt(Window::window_ptr window, int top, int left, bool cull);

    int getElevation() const;
    void setElevation(int elevationInput);
    int getType() const;
    void setType(int tileInput);

    static void init();

    static const int elevationMax = 128;
    static const int TypeCount = 8;
    static const int allowedSpawnCount = 7;
    static const int allowedCityCount = 5;

    static const int AllowedSpawns[allowedSpawnCount];
    static const int TilesWhichMayHaveCities[allowedCityCount];

    struct TileType
    {
        char tile;
        unsigned int colorPair;
        unsigned int elevationMin;
        unsigned int elevationMax;
        unsigned int livability; // 0 - 10

        TileType(
            char tile, 
            unsigned int colorPair,
            unsigned int elevationMin,
            unsigned int elevationMax,
            unsigned int livability
        ) : tile(tile), 
            colorPair(colorPair),
            elevationMin(elevationMin),
            elevationMax(elevationMax),
            livability(livability)
        {}
    };

    /**
     * Static array of TileType to work as a lookup map, tiles contain the
     * index of their own type to get all metadata about that type from this
     * map.
     */
    static const TileType Tiles[TypeCount]; 

private:
    static ColorPallete tilePallete;
    static bool colorPalleteInitialized;

    /**
     * Index into Tiles 
     */
    int myType;
    int myElevation;
    bool hasBeenVisible;
};

#endif //TILE_HPP
