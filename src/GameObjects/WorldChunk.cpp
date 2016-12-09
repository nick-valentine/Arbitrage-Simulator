#include "GameObjects/WorldChunk.hpp"

const std::string WorldChunk::SpaceConstant = " ";
const std::string WorldChunk::CityMarker = "city";
const std::string WorldChunk::MapMarker = "MAP";
    
std::map<std::string, void (*)(WorldChunk *self, std::stringstream *ss)> WorldChunk::factoryMap = 
    {
        {WorldChunk::CityMarker, spawnCity}
    }; 

bool WorldChunk::configured = false;
unsigned int WorldChunk::chunk_height = 0;
unsigned int WorldChunk::chunk_width = 0;
int WorldChunk::max_cities_per_chunk = 0;

int WorldChunk::maxY = 0;
int WorldChunk::maxX = 0;

WorldChunk::WorldChunk()
{
    if(!WorldChunk::configured) {
        this->configure();
    } 
}

WorldChunk::WorldChunk(std::stringstream *ss)
{
    this->fromStringStream(ss);
    if(!WorldChunk::configured) {
        this->configure();
    } 
}

void WorldChunk::setMaxYX(unsigned int y, unsigned int x)
{
    WorldChunk::maxY = y;
    WorldChunk::maxX = x;
}

void WorldChunk::configure()
{
    WorldChunk::chunk_height = ConfigLoader::getIntOption("chunk_height", 30);
    WorldChunk::chunk_width = ConfigLoader::getIntOption("chunk_width", 30);
    WorldChunk::max_cities_per_chunk = ConfigLoader::getIntOption("max_cities_per_chunk", 5);
    WorldChunk::configured = true;
}

void WorldChunk::fromStringStream(std::stringstream *ss)
{
    READ_STATE readState = object;
    std::vector<Tile> tilesToSpawn;
    std::string nextObject;
    while(ss->good()) {
        if(readState == object) {
            (*ss)>>nextObject;
            if( this->factoryMap.find(nextObject) != this->factoryMap.end() ) {
                this->factoryMap[nextObject](this, ss);
            } else if( nextObject == "MAP" ) {
                readState = map;
                tilesToSpawn.push_back(Tile(ss));
            }
        } else if(readState == map) {
            tilesToSpawn.push_back(Tile(ss));
        }
    }    
    this->organizeTiles(tilesToSpawn);
}

void WorldChunk::toStringStream(std::stringstream *ss)
{
    for(unsigned int i = 0; i < this->cities.size(); ++i) {
        (*ss)<<WorldChunk::CityMarker<<WorldChunk::SpaceConstant;
        this->cities[i].toStringStream(ss);
    }
    (*ss)<<WorldChunk::MapMarker<<WorldChunk::SpaceConstant;
    for(unsigned int i = 0; i < this->tiles.size(); ++i) {
        for(unsigned int j = 0; j < this->tiles[i].size(); ++j) {
            this->tiles[i][j].toStringStream(ss); 
            (*ss)<<SpaceConstant;
        }
    }
}

void WorldChunk::generateChunk()
{
    this->cities.clear();
    this->tiles.clear();

    //@todo: base this off of a noise function rather than rand
    for(unsigned int i = 0; i < WorldChunk::chunk_height; ++i) {
        this->tiles.push_back(std::vector<Tile>());
        for( unsigned int j = 0; j < WorldChunk::chunk_width; ++j) {
            this->tiles[i].push_back(Tile::randomSpawn()); 
        }
    }

    int num_cities = rand() % WorldChunk::max_cities_per_chunk;

    //@todo: make sure no two cities spawn on or near eachother
    for(unsigned int i = 0; i < num_cities; ++i) {
        std::string cityName = 
            City::city_name_starts[rand() % City::city_name_starts.size()] 
            + City::city_name_ends[rand() % City::city_name_ends.size()]
        ;
        this->cities.push_back(City(cityName, rand() % WorldChunk::chunk_height, rand() % WorldChunk::chunk_width));
    }

    for(unsigned int i = 0;  i < cities.size(); ++i) {
        unsigned int x, y;
        x = cities[i].getPosX();
        y = cities[i].getPosY();
       tiles[y][x] = Tile::CITIES; 
    }
}

void WorldChunk::spawnCity(WorldChunk *self, std::stringstream *ss)
{
    self->cities.push_back(City(ss));
}

void WorldChunk::organizeTiles(std::vector<Tile> tiles)
{
    for(unsigned int i = 0; i < WorldChunk::chunk_height; ++i) {
        this->tiles.push_back(std::vector<Tile>());
        for( unsigned int j = 0; j < WorldChunk::chunk_width; ++j) {
            this->tiles[i].push_back(tiles[(i*WorldChunk::chunk_height) + j]);
        }
    }
}


void WorldChunk::draw(unsigned int top, unsigned int left)
{
    int currX, currY;
    Tile::setPallete();
    for(unsigned int i = 0; i < WorldChunk::chunk_height; ++i) {
        getyx(stdscr, currY, currX);
        if(currY < WorldChunk::maxY && currX < WorldChunk::maxX) {
            move(top + i, left);
            for(unsigned int j = 0; j < WorldChunk::chunk_width; ++j) {
                getyx(stdscr, currY, currX);
                if(currX < WorldChunk::maxX) {
                    this->tiles[i][j].draw();
                } else {
                    continue;
                }
            }
        } else {
            break;
        }
    }    
}
