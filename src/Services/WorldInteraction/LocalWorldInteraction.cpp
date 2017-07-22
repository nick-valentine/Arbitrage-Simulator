#include "Services/WorldInteraction/LocalWorldInteraction.hpp"

LocalWorldInteraction::LocalWorldInteraction() : World("")
{
    this->playerY = 0;
    this->playerX = 0;
    this->generator = Generator::DefaultGenerator();
}

LocalWorldInteraction::LocalWorldInteraction(std::string worldName) : World(worldName)
{
    this->playerY = 0;
    this->playerX = 0;
    this->generator = Generator::DefaultGenerator();
}

void LocalWorldInteraction::loadWorld(Logger *logger)
{
    this->generateWorld();

    this->generator.execute(this, logger);
}

void LocalWorldInteraction::draw(Window::window_ptr window)
{
    World::draw(window, this->playerY, this->playerX);
}

void LocalWorldInteraction::movePlayerToCoordinate(int y, int x)
{
    this->playerY = y;
    this->playerX = x;
}


void LocalWorldInteraction::playerCoordinatesToChunkCoordinates(
    int &chunkY, int &chunkX,
    int &Y, int &X
) {
    this->globalCoordinatesToChunkCoordinates(
        this->playerY, this->playerX,
        chunkY, chunkX,
        Y, X
    );
}

void LocalWorldInteraction::globalCoordinatesToChunkCoordinates(
    int inY, int inX, 
    int &chunkY, int &chunkX, 
    int &outY, int &outX
) {
    chunkY = inY / this->chunkHeight;
    outY = inY % this->chunkHeight;

    chunkX = inX / this->chunkWidth;
    outX = inX % this->chunkWidth;
}

WorldChunk LocalWorldInteraction::getChunk(int y, int x) const
{
    if (y < this->chunks.size() && x < this->chunks[y].size()) {
        return this->chunks[y][x];
    }
    return WorldChunk();
}
