#include "Services/WorldInteraction/LocalWorldInteraction.hpp"

LocalWorldInteraction::LocalWorldInteraction() : World("")
{
    this->generator = Generator::DefaultGenerator();
}

LocalWorldInteraction::LocalWorldInteraction(std::string worldName) : World(worldName)
{
    this->generator = Generator::DefaultGenerator();
}

bool LocalWorldInteraction::loadWorld(boost::shared_ptr<Logger> logger)
{
    ItemMap::init(logger);

    this->generateWorld();

    this->generator.execute(this, logger);

    return true;
}

void LocalWorldInteraction::cleanup()
{

}

void LocalWorldInteraction::draw(Window::window_ptr window, int offsetTop, int offsetLeft)
{
    World::draw(window, offsetTop, offsetLeft);
    for (int i = 0; i < this->players.size(); ++i) {
        this->players[i].draw(window, offsetTop, offsetLeft);
    }
}

void LocalWorldInteraction::movePlayer(int index, int y, int x)
{
    this->players[index].move(y, x);
}

Tile LocalWorldInteraction::getTileUnderPlayer(int index)
{
    int chunkY, chunkX, localY, localX;
    this->playerCoordinatesToChunkCoordinates(index, chunkY, chunkX, localY, localX);
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
    int index,
    int &chunkY, int &chunkX,
    int &Y, int &X
) {
    int playerY, playerX;
    this->players[index].getYX(playerY, playerX);
    this->globalCoordinatesToChunkCoordinates(
        playerY, playerX,
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

int LocalWorldInteraction::getPlayer(std::string name)
{
    for (int i = 0; i < this->players.size(); ++i) {
        if (this->players[i].getName() == name) {
            return i;
        }
    }
    this->players.push_back(Player(name, 200, 200));
    return this->players.size() - 1;
}

Player LocalWorldInteraction::playerInfo(int index)
{
    if (index != -1) {
        return this->players[index];
    }
    return Player();
}

int LocalWorldInteraction::getChunkHeight()
{
    return this->chunkHeight;
}

int LocalWorldInteraction::getChunkWidth()
{
    return this->chunkWidth;
}

int LocalWorldInteraction::getWorldHeight()
{
    return World::worldHeight;
}

int LocalWorldInteraction::getWorldWidth()
{
    return World::worldWidth;
}

void LocalWorldInteraction::playersToStringstream(std::stringstream *ss)
{
    for (int i = 0; i < this->players.size(); ++i) {
        this->players[i].toStringStream(ss);
    }
}

void LocalWorldInteraction::playersFromStringstream(std::stringstream *ss)
{
    this->players.clear();
    while ((*ss).good()) {
        Player player(ss);
        this->players.push_back(player);
    }
}
