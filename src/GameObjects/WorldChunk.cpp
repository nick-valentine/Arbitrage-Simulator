#include "GameObjects/WorldChunk.hpp"

const std::string WorldChunk::SpaceConstant = " ";
const std::string WorldChunk::CityMarker = "city";
const std::string WorldChunk::MapMarker = "MAP";
    
std::map<std::string, void (*)(WorldChunk *self, std::stringstream *ss)> WorldChunk::factoryMap = 
    {
        {WorldChunk::CityMarker, spawnCity}
    }; 

const std::vector<std::string> WorldChunk::city_name_starts = 
    {
        "Oaken",
        "Wilken",
        "Shrunken",
        "Fulmilka",
        "Rolling",
        "High"
    };

const std::vector<std::string> WorldChunk::city_name_ends = 
    {
        "greens",
        "frost",
        "plains",
        "woods",
        "shire",
        "chestir"
    };

bool WorldChunk::configured = false;
unsigned int WorldChunk::chunk_height = 0;
unsigned int WorldChunk::chunk_width = 0;
int WorldChunk::max_cities_per_chunk = 0;

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

void WorldChunk::configure()
{
    WorldChunk::chunk_height = ConfigLoader::getIntOption("chunk_height");
    WorldChunk::chunk_width = ConfigLoader::getIntOption("chunk_width");
    WorldChunk::max_cities_per_chunk = ConfigLoader::getIntOption("max_cities_per_chunk");
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
            this->tiles[i].push_back(Tile(rand() % Tile::TypeCount)); 
        }
    }

    int num_cities = rand() % WorldChunk::max_cities_per_chunk;

    //@todo: make sure no two cities spawn on or near eachother
    for(unsigned int i = 0; i < num_cities; ++i) {
        std::string cityName = 
            city_name_starts[rand() % city_name_starts.size()] 
            + city_name_ends[rand() % city_name_ends.size()]
        ;
        this->cities.push_back(City(cityName, rand() % WorldChunk::chunk_height, rand() % WorldChunk::chunk_width));
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

