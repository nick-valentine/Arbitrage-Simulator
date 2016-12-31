#include "GameObjects/World.hpp"

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
    for(int i = 0; i < 20; ++i) {
        for(int j = 0; j < 20; ++j) {
            this->spawnChunk(j, i);
        }
    }
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
            this->chunks[fillY].push_back(this->prepareChunk(y, x));
        }
    }

    for(int i = 0; i < dx; ++i) {
        for(int j = 0; j < this->chunks.size(); ++j) {
            this->chunks[j].push_back(this->prepareChunk(y, x));
        }
    }
}

WorldChunk World::prepareChunk(int y, int x)
{
    WorldChunk temp(y, x);
    temp.generateChunk(&this->tileNoise, &this->elevationNoise, &this->elevationSkewNoise);
    return temp;
}
