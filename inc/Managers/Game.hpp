#ifndef MANAGER_GAME_HPP
#define MANAGER_GAME_HPP

#include <iostream>
#include <curses.h>
#include <string>
#include <stdio.h>

#include "Camera.hpp"
#include "ConfigLoader.hpp"
#include "GameObjects/City.hpp"
#include "GameObjects/Player.hpp"
#include "Services/WorldInteraction/WorldInteractionInterface.hpp"
#include "Services/WorldInteraction/LocalWorldInteraction.hpp"
#include "Services/WorldInteraction/NetworkedWorldInteraction.hpp"
#include "Window/Window.hpp"
#include "Window/GameWindow.hpp"

using boost::asio::ip::tcp;

/**
 * Manager for Game State.
 * Main interface for players playing the game.
 */
class Game
{
public:
    Game();
    ~Game();
    int setup();
    int run();
private:
    static const std::string configWorldNameKey;
    static const std::string defaultWorldName;

    void configure();

    Camera camera;
    GameWindow gameWindow;
    Player player;
    WorldInteractionInterface *worldProxy;

    int screenHeight;
    int screenWidth;
};

#endif //MANAGER_GAME_HPP
