#include "Managers/Game.hpp"

const std::string Game::configWorldNameKey = "world_name";
const std::string Game::defaultWorldName = "world";

Game::Game()
{

}

int Game::setup()
{
    this->configure();

    this->camera = Camera(10, 10);
    this->screen = Screen();

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
    this->camera.render(this->screen, this->world);
    this->screen.render();
    //this->world.draw(0, 0);
    return getch();
}

void Game::configure()
{
    WorldChunk::configure();
    City::load_city_names();
}
