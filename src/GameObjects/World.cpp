#include "GameObjects/World.hpp"

unsigned int World::worldHeight = 0;
unsigned int World::worldWidth = 0;

World::World()
{
    this->init();
}

World::World(std::stringstream *ss)
{
    this->init();
    this->fromStringStream(ss);
}

World::World(std::string name)
{
    this->init();
    this->name = name;
}

void World::configure()
{
    World::worldHeight = ConfigLoader::getIntOption("world_height", 20);
    World::worldWidth = ConfigLoader::getIntOption("world_width", 20);
}

void World::fromStringStream(std::stringstream *ss)
{
    int sizeY, sizeX;
    (*ss)>>this->name>>this->creationTimestamp;
    (*ss)>>sizeY>>sizeX;
    for(int i = 0; i < sizeY; ++i) {
            this->chunks.push_back(std::vector<WorldChunk>());
        for(int j = 0; j < sizeX; ++j) {
            this->chunks[i].push_back(WorldChunk(ss));
        }
    }
}

void World::toStringStream(std::stringstream *ss)
{
    (*ss)<<this->name<<" "<<this->creationTimestamp<<" ";
    (*ss)<<this->chunks.size()<<" "<<this->chunks[0].size()<<"\n";
    for(int i = 0; i < this->chunks.size(); ++i) {
        for(int j = 0; j < this->chunks[i].size(); ++j) {
            this->chunks[i][j].toStringStream(ss);
            (*ss)<<"\n";
        }
    }
}

void World::generateWorld()
{
    this->creationTimestamp = time(NULL);

    //spawning the bottom left chunk spawns all interim chunks.
    this->spawnChunk(World::worldHeight, World::worldWidth);
}

void World::draw(Screen &screen, int playerY, int playerX)
{
    for(int i = 0; i < this->chunks.size(); ++i) {
        for(int j = 0; j < this->chunks[i].size(); ++j) {
            this->chunks[i][j].draw(screen, playerY, playerX);
        }
    }
}

void World::init()
{
    this->elevationSkewNoise = NoiseFunc(World::elevationSkewNoiseSpread);
    this->elevationNoise = NoiseFunc(World::elevationNoiseSpread);
    this->tileNoise = NoiseFunc(World::tileNoiseSpread);

    this->chunkHeight = WorldChunk::getChunkHeight();
    this->chunkWidth = WorldChunk::getChunkWidth();
}

void World::spawnChunk(int y, int x)
{
    int size_y = this->chunks.size();
    int size_x = (size_y > 0) ? this->chunks[0].size() : 0;
    int dy = (y+1) - size_y; 
    int dx = (x+1) - size_x; 

    for(int i = 0; i < dy; ++i) {
        this->chunks.push_back(std::vector<WorldChunk>());
        int fillY = this->chunks.size() - 1;
        for(int j = 0; j < chunks[0].size(); ++j) {
            this->chunks[fillY].push_back(this->prepareChunk(fillY, j));
        }
    }

    for(int i = 0; i < dx; ++i) {
        for(int j = 0; j < this->chunks.size(); ++j) {
            this->chunks[j].push_back(this->prepareChunk(j, i));
        }
    }
}

WorldChunk World::prepareChunk(int y, int x)
{
    WorldChunk temp(y, x);
    temp.generateChunk(&this->tileNoise, &this->elevationNoise, &this->elevationSkewNoise);
    return temp;
}

int World::getWorldHeight()
{
    return World::worldHeight;
}

int World::getWorldWidth()
{
    return World::worldWidth;
}
