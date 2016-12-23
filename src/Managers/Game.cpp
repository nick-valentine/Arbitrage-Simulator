#include "Managers/Game.hpp"

const std::string Game::configWorldNameKey = "world_name";
const std::string Game::defaultWorldName = "world";

Game::Game()
{

}

int Game::setup()
{
    this->world = World(
        ConfigLoader::getStringOption(
            Game::configWorldNameKey,
            Game::defaultWorldName
        )
    );
    this->world.generateWorld();
}

int Game::run()
{
    this->world.draw(0, 0);
    return getch();
}
