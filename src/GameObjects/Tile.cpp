#include "GameObjects/Tile.hpp"

const int Tile::AllowedSpawns[Tile::allowedSpawnCount] = 
{
    0, 1, 2, 3
};

const Tile::TileType Tile::Tiles[Tile::TypeCount] = 
{ 
    {'.'}, //plains
    {'M'}, //mountains
    {'O'}, //water
    {'s'}, //swamps
    {'C'} //Cities
};

Tile::Tile()
{
    this->myType = 0;
}

Tile::Tile(int type)
{
    this->myType = type;
}

Tile Tile::randomSpawn()
{
    return Tile(AllowedSpawns[rand() % Tile::allowedSpawnCount]);  
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

void Tile::draw()
{
    addch(Tile::Tiles[myType].tile); 
}
