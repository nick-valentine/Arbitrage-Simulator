#include "GameObjects/Tile.hpp"

const int Tile::AllowedSpawns[Tile::allowedSpawnCount] = 
{
    0, 1, 2, 3, 5, 6, 7
};

const int Tile::TilesWhichMayHaveCities[Tile::allowedCityCount] =
{
    0, 1, 5, 6, 7 
};

const Tile::TileType Tile::Tiles[Tile::TypeCount] = 
{ 
    {'-', 5, 30, 60},  //plains
    {'^', 1, 50, 128}, //mountains
    {'#', 2, 0,  40},  //water
    {'#', 3, 20, 40},  //swamps
    {'C', 4, 0,  0},   //Cities
    {'n', 5, 45, 80},  //Hills
    {'_', 0, 20, 30},  //Deserts
    {'T', 3, 45, 75}   //Forests
};

ColorPallete Tile::tilePallete = ColorPallete();
bool Tile::colorPalleteInitialized = false;

Tile::Tile()
{
    this->myType = 0;
    this->hasBeenVisible = false;
    Tile::init();
}

Tile::Tile(int type, int elevation)
{
    this->myType = type;
    this->myElevation = elevation;
    this->hasBeenVisible = false;
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
    (*ss)>>myType>>myElevation>>hasBeenVisible;
}

void Tile::toStringStream(std::stringstream *ss)
{
    (*ss)<<myType<<" "<<myElevation<<" "<<hasBeenVisible;
}

void Tile::setPallete()
{
    Tile::tilePallete.setCurrent();    
}

bool Tile::convertToCity()
{
    bool canConvert = false;
    for(int i = 0; i < Tile::allowedCityCount; ++i) {
        if(this->myType == Tile::TilesWhichMayHaveCities[i]) {
            canConvert = true;
            break;
        }
    }

    if(canConvert) { 
        this->myType = TilesReserved::CITIES;
        return true;
    }
    return false;
}

void Tile::drawAt(Screen &screen, int top, int left, bool cull)
{
    if(!cull) {
        screen.put(
            Tile::Tiles[myType].colorPair,
            /* layer */ 1,
            Tile::Tiles[myType].tile,
            top,
            left
        ); 
        this->hasBeenVisible = true;
    } else if(this->hasBeenVisible) {
        screen.put(
            /* White on Black */ 5,
            /* layer */ 1,
            Tile::Tiles[myType].tile,
            top,
            left
        ); 
    }
}

void Tile::init()
{
    if(!Tile::colorPalleteInitialized) {
        Tile::tilePallete.addColor(COLOR_YELLOW, COLOR_BLACK);
        Tile::tilePallete.addColor(COLOR_RED,    COLOR_BLACK);
        Tile::tilePallete.addColor(COLOR_BLUE,   COLOR_BLACK);
        Tile::tilePallete.addColor(COLOR_GREEN,  COLOR_BLACK);
        Tile::tilePallete.addColor(COLOR_CYAN,   COLOR_BLACK);
        Tile::tilePallete.addColor(COLOR_WHITE, COLOR_BLACK);

        Tile::colorPalleteInitialized = true;
    }
}

int Tile::getElevation() const
{
    return this->myElevation;
}

int Tile::getType() const
{
    return this->myType;
}
