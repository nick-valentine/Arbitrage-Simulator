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

void LocalWorldInteraction::loadWorld(boost::shared_ptr<Logger> logger)
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

Tile LocalWorldInteraction::getTileUnderPlayer()
{
    int chunkY, chunkX, localY, localX;
    this->playerCoordinatesToChunkCoordinates(chunkY, chunkX, localY, localX);
    return this->chunks[chunkY][chunkX].tiles[localY][localX];
}

City LocalWorldInteraction::getCity(int y, int x)
{
    int chunkY, chunkX, localY, localX;
    this->globalCoordinatesToChunkCoordinates(
        y, x,
        chunkY, chunkX,
        localY, localX
    );
    return this->chunks[chunkY][chunkX].getCity(localY, localX);
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

bool LocalWorldInteraction::chunkInWorld(int chunkY, int chunkX)
{
    if (
        chunkY > 0 && chunkY < World::getWorldHeight() &&
        chunkX > 0 && chunkX < World::getWorldWidth()
    ) {
        return true;
    }
    return false;
}

WorldChunk LocalWorldInteraction::getChunk(int y, int x) const
{
    if (y < this->chunks.size() && x < this->chunks[y].size()) {
        return this->chunks[y][x];
    }
    return WorldChunk();
}
