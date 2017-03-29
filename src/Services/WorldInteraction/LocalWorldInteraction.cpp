#include "Services/WorldInteraction/LocalWorldInteraction.hpp"

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
