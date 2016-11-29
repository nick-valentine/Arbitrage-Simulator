#ifndef TILE_HPP
#define TILE_HPP

#include <sstream>
#include <string>

#include "GameObjects/AbstractGameObject.hpp"

class Tile : public AbstractGameObject
{
public:
    Tile();
    Tile(int type);
    Tile(std::stringstream *ss);
    void fromStringStream(std::stringstream *ss);
    void toStringStream(std::stringstream *ss);

    static const int TypeCount = 4;

private:
    // @todo: add colors etc.
    struct TileType
    {
        char tile;

        TileType(char tile) : tile(tile) {}
    };

    static const TileType Tiles[TypeCount]; 

    //index into Tiles 
    int myType;
};

#endif //TILE_HPP
