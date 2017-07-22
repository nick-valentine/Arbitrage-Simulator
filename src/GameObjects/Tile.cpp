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
    {'-', 6, 30, 60},  //plains
    {'^', 2, 50, 128}, //mountains
    {'#', 3, 0,  40},  //water
    {'#', 4, 20, 40},  //swamps
    {'C', 5, 0,  0},   //Cities
    {'n', 6, 45, 80},  //Hills
    {'_', 1, 20, 30},  //Deserts
    {'T', 4, 45, 75}   //Forests
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

void Tile::setElevation(float elevationInput)
{
    if(elevationInput == -1) {
        this->myElevation = rand() % Tile::elevationMax; 
        return;
    } 
    this->myElevation = abs(elevationInput * (float)Tile::elevationMax);
}

void Tile::setType(float tileInput)
{
    int spawn = -1;
    std::vector<int> spawnsAllowedAtThisElevation;
    for(int i = 0; i < Tile::allowedSpawnCount; ++i) {
        unsigned int min = Tile::Tiles[Tile::AllowedSpawns[i]].elevationMin;
        unsigned int max = Tile::Tiles[Tile::AllowedSpawns[i]].elevationMax;
        if(this->myElevation >= min && this->myElevation <= max) {
            spawnsAllowedAtThisElevation.push_back(AllowedSpawns[i]);
        }
    }
    if(spawnsAllowedAtThisElevation.size() == 0) {
        std::cout<<"ERROR: Can not spawn tile at elevation "<<this->myElevation<<std::endl;
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
    this->myType = spawn;
}

Tile::Tile(std::stringstream *ss)
{
    this->fromStringStream(ss);
}

void Tile::fromStringStream(std::stringstream *ss)
{
    (*ss)>>myType>>myElevation>>hasBeenVisible;
    Tile::init();
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

void Tile::drawAt(Window::window_ptr window, int top, int left, bool cull)
{
    if(!cull) {
        window->put(
            Tile::Tiles[myType].colorPair,
            /* layer */ 1,
            Tile::Tiles[myType].tile,
            top,
            left
        ); 
        this->hasBeenVisible = true;
    } else if(this->hasBeenVisible) {
        window->put(
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
