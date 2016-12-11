#include "GameObjects/Tile.hpp"

const int Tile::AllowedSpawns[Tile::allowedSpawnCount] = 
{
    0, 1, 2, 3
};

const Tile::TileType Tile::Tiles[Tile::TypeCount] = 
{ 
    {'-', 0, 30, 60},  //plains
    {'^', 1, 50, 128}, //mountains
    {'.', 2, 0,  40},  //water
    {',', 3, 20, 40},  //swamps
    {'C', 4, 0,  0}    //Cities
};

ColorPallete Tile::tilePallete = ColorPallete();
bool Tile::colorPalleteInitialized = false;

Tile::Tile()
{
    this->myType = 0;
    Tile::init();
}

Tile::Tile(int type, int elevation)
{
    this->myType = type;
    this->myElevation = elevation;
    Tile::init();

}

Tile Tile::randomSpawn(float tileInput, float elevationInput)
{
    Tile::init();
    int spawn = -1;
    int elevation = -1;
    
    if(elevationInput == -1) {
        elevation = rand() % Tile::elevationMax; 
    } else {
        elevation = abs(elevationInput * (float)Tile::elevationMax);
    }
    
    std::vector<int> spawnsAllowedAtThisElevation;
    for(int i = 0; i < Tile::allowedSpawnCount; ++i) {
        unsigned int min = Tile::Tiles[Tile::AllowedSpawns[i]].elevationMin;
        unsigned int max = Tile::Tiles[Tile::AllowedSpawns[i]].elevationMax;
        if(elevation >= min && elevation <= max) {
            spawnsAllowedAtThisElevation.push_back(AllowedSpawns[i]);
        }
    }
    if(spawnsAllowedAtThisElevation.size() == 0) {
        std::cout<<"ERROR: Can not spawn tile at elevation "<<elevation<<std::endl;
        exit(1);
    }

    if(tileInput == -1) {
        spawn = spawnsAllowedAtThisElevation[rand() % spawnsAllowedAtThisElevation.size()];
    } else {
        float tileToSpawn = tileInput;
        tileToSpawn *= Tile::veryLargeMultiplyer;
        int indexToSpawn = abs((int)tileToSpawn);
        indexToSpawn %= spawnsAllowedAtThisElevation.size();
        spawn = spawnsAllowedAtThisElevation[indexToSpawn];
    }
    
    return Tile(spawn, elevation);  
}

Tile::Tile(std::stringstream *ss)
{
    this->fromStringStream(ss);
}

void Tile::fromStringStream(std::stringstream *ss)
{
    (*ss)>>myType>>myElevation;
}

void Tile::toStringStream(std::stringstream *ss)
{
    (*ss)<<myType<<" "<<myElevation;
}

void Tile::setPallete()
{
    Tile::tilePallete.setCurrent();    
}

void Tile::convertToCity()
{
    this->myType = TilesReserved::CITIES;
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
        Tile::tilePallete.addColor(COLOR_RED,    COLOR_BLACK);
        Tile::tilePallete.addColor(COLOR_BLUE,   COLOR_BLACK);
        Tile::tilePallete.addColor(COLOR_GREEN,  COLOR_BLACK);
        Tile::tilePallete.addColor(COLOR_CYAN,   COLOR_BLACK);
        Tile::colorPalleteInitialized = true;
    }
}
