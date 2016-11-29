#include "GameObjects/Tile.hpp"

const Tile::TileType Tile::Tiles[Tile::TypeCount] = 
{ 
    {'.'}, //plains
    {'M'}, //mountains
    {'O'}, //water
    {'s'} //swamps
};

Tile::Tile()
{
    this->myType = 0;
}

Tile::Tile(int type)
{
    this->myType = type;
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
