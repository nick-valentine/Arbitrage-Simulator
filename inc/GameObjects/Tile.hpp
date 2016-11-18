#ifndef TILE_HPP
#define TILE_HPP

#include <sstream>
#include <string>

#include "GameObjects/AbstractGameObject.hpp"

class Tile : public AbstractGameObject
{
public:
    Tile();
    Tile(std::stringstream *ss);
    void fromStringStream(std::stringstream *ss);
    void toStringStream(std::stringstream *ss);


private:
    // @todo: add colors etc.
    struct TileType
    {
        char tile;

        TileType(char tile) : tile(tile) {}
    };

    static const TileType Tiles[4]; 

    //index into Tiles 
    int myType;
};

#endif //TILE_HPP
