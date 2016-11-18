#include "GameObjects/WorldChunk.hpp"

const std::string WorldChunk::SpaceConstant = " ";
const std::string WorldChunk::CityMarker = "city";
const std::string WorldChunk::MapMarker = "MAP";
    
std::map<std::string, void (*)(WorldChunk *self, std::stringstream *ss)> WorldChunk::factoryMap = 
    {
        {WorldChunk::CityMarker, spawnCity}
    }; 

WorldChunk::WorldChunk()
{
    
}

WorldChunk::WorldChunk(std::stringstream *ss)
{
    this->fromStringStream(ss);
}

void WorldChunk::fromStringStream(std::stringstream *ss)
{
    READ_STATE readState = object;
    std::string nextObject;
    while(ss->good()) {
        if(readState == object) {
            (*ss)>>nextObject;
            if( this->factoryMap.find(nextObject) != this->factoryMap.end() ) {
                this->factoryMap[nextObject](this, ss);
            } else if( nextObject == "MAP" ) {
                readState = map;
                this->spawnTile(this, ss);
            }
        } else if(readState == map) {
            this->spawnTile(this, ss);
        }
    }    
}

void WorldChunk::toStringStream(std::stringstream *ss)
{
    for(unsigned int i = 0; i < this->cities.size(); ++i) {
        (*ss)<<WorldChunk::CityMarker<<WorldChunk::SpaceConstant;
        this->cities[i].toStringStream(ss);
    }
    (*ss)<<WorldChunk::MapMarker<<WorldChunk::SpaceConstant;
    for(unsigned int i = 0; i < this->tiles.size(); ++i) {
        this->tiles[i].toStringStream(ss); 
        (*ss)<<SpaceConstant;
    }
}

void WorldChunk::spawnCity(WorldChunk *self, std::stringstream *ss)
{
    self->cities.push_back(City(ss));
}

void WorldChunk::spawnTile(WorldChunk *self, std::stringstream *ss)
{
    self->tiles.push_back(Tile(ss));
}

