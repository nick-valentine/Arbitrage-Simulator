#ifndef MANAGER_GAME_HPP
#define MANAGER_GAME_HPP

#include <iostream>
#include <curses.h>

#include "Camera.hpp"
#include "ConfigLoader.hpp"
#include "GameObjects/City.hpp"
#include "GameObjects/Player.hpp"
#include "GameObjects/World.hpp"
#include "GameObjects/WorldChunk.hpp"
#include "Screen.hpp"

class Game
{
public:
    Game();
    int setup();
    int run();
private:
    static const std::string configWorldNameKey;
    static const std::string defaultWorldName;

    void configure();

    Camera camera;
    Screen screen;
    World world;
    Player player;

    int screenHeight;
    int screenWidth;
};

#endif //MANAGER_GAME_HPP
