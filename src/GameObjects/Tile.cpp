#include "GameObjects/Tile.hpp"

const int Tile::AllowedSpawns[Tile::allowedSpawnCount] = 
{
    0, 1, 2, 3
};

const Tile::TileType Tile::Tiles[Tile::TypeCount] = 
{ 
    {'#', 0}, //plains
    {'M', 1}, //mountains
    {'O', 2}, //water
    {'s', 3}, //swamps
    {'C', 4} //Cities
};

ColorPallete Tile::tilePallete = ColorPallete();
bool Tile::colorPalleteInitialized = false;

Tile::Tile()
{
    this->myType = 0;
    Tile::init();
}

Tile::Tile(int type)
{
    this->myType = type;
    Tile::init();

}

Tile Tile::randomSpawn(float randomInput)
{
    Tile::init();
    int spawn = -1;
    if(randomInput == -1) {
        spawn = AllowedSpawns[rand() % Tile::allowedSpawnCount];
    } else {
        spawn = AllowedSpawns[(int)abs((randomInput * Tile::veryLargeMultiplyer)) % Tile::allowedSpawnCount];
    }
    return Tile(spawn);  
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

void Tile::setPallete()
{
    Tile::tilePallete.setCurrent();    
}

void Tile::draw()
{
    attrset(COLOR_PAIR(Tile::Tiles[myType].colorPair));
    addch(Tile::Tiles[myType].tile); 
}

void Tile::init()
{
    if(!Tile::colorPalleteInitialized) {
        Tile::tilePallete.addColor(COLOR_YELLOW, COLOR_BLACK);
        Tile::tilePallete.addColor(COLOR_WHITE,  COLOR_BLACK);
        Tile::tilePallete.addColor(COLOR_BLUE,   COLOR_BLACK);
        Tile::tilePallete.addColor(COLOR_GREEN,  COLOR_BLACK);
        Tile::tilePallete.addColor(COLOR_CYAN,   COLOR_BLACK);
        Tile::colorPalleteInitialized = true;
    }
}
