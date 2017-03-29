#include "Services/WorldInteraction/LocalWorldInteraction.hpp"

LocalWorldInteraction::LocalWorldInteraction(std::string worldName)
{
    this->world = World(worldName);
    this->playerY = 0;
    this->playerX = 0;
}

void LocalWorldInteraction::loadWorld()
{
    this->world.generateWorld();
}

void LocalWorldInteraction::draw(Screen &screen)
{
    this->world.draw(screen, this->playerY, this->playerX);
}

void LocalWorldInteraction::movePlayerToCoordinate(int y, int x)
{
    this->playerY = y;
    this->playerX = x;
}
