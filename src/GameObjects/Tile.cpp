#include "GameObjects/Tile.hpp"

const Tile::TileType Tile::Tiles[4] = 
{ 
    {'.'}, //plains
    {'M'}, //mountains
    {'O'}, //water
    {'s'} //swamps
};

Tile::Tile()
{
    myType = 0;
}

Tile::Tile(std::stringstream *ss)
{
    this->fromStringStream(ss);
}

void Tile::fromStringStream(std::stringstream *ss)
{
    (*ss)>>myType;
}

void Tile::toStringStream(std::stringstream *ss)
{
    (*ss)<<myType;
}
