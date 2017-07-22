#ifndef MANAGER_GAME_HPP
#define MANAGER_GAME_HPP

#include <iostream>
#include <curses.h>
#include <string>
#include <stdio.h>
#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>

#include "Camera.hpp"
#include "ConfigLoader.hpp"
#include "GameObjects/City.hpp"
#include "GameObjects/Player.hpp"
#include "Services/WorldInteraction/WorldInteractionInterface.hpp"
#include "Services/WorldInteraction/LocalWorldInteraction.hpp"
#include "Services/WorldInteraction/NetworkedWorldInteraction.hpp"
#include "Services/WindowLayout/GameWindowLayout.hpp"
#include "Services/Logger/Logger.hpp"
#include "Window/Window.hpp"
#include "Window/GameWindow.hpp"
#include "Window/ConsoleWindow.hpp"

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

    boost::shared_ptr<Logger> logger;

    void configure();

    Camera camera;
    GameWindowLayout windowLayout;
    Window::window_ptr gameWindow;
    Window::window_ptr consoleWindow;
    Player player;
    WorldInteractionInterface *worldProxy;

    int screenHeight;
    int screenWidth;
};

#endif //MANAGER_GAME_HPP
