#ifndef MANAGER_GAME_HPP
#define MANAGER_GAME_HPP

#include <curses.h>

#include "ConfigLoader.hpp"
#include "GameObjects/World.hpp"

class Game
{
public:
    Game();
    int setup();
    int run();
private:
    static const std::string configWorldNameKey;
    static const std::string defaultWorldName;

    World world;
};

#endif //MANAGER_GAME_HPP
