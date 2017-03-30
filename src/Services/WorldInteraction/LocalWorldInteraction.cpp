#include "Services/WorldInteraction/LocalWorldInteraction.hpp"

LocalWorldInteraction::LocalWorldInteraction() : World("")
{
    this->playerY = 0;
    this->playerX = 0;
}

LocalWorldInteraction::LocalWorldInteraction(std::string worldName) : World(worldName)
{
    this->playerY = 0;
    this->playerX = 0;
}

void LocalWorldInteraction::loadWorld()
{
    this->generateWorld();
}

void LocalWorldInteraction::draw(Screen &screen)
{
    World::draw(screen, this->playerY, this->playerX);
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
