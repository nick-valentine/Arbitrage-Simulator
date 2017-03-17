#ifndef MANAGER_GAME_HPP
#define MANAGER_GAME_HPP

#include <iostream>
#include <curses.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include "Server.hpp"
#include "Camera.hpp"
#include "ConfigLoader.hpp"
#include "GameObjects/City.hpp"
#include "GameObjects/Player.hpp"
#include "GameObjects/World.hpp"
#include "GameObjects/WorldChunk.hpp"
#include "Screen.hpp"
#include "Networking/Connection.hpp"

using boost::asio::ip::tcp;

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
    std::string version;

    Camera camera;
    Screen screen;
    World world;
    Player player;

    int screenHeight;
    int screenWidth;

    Connection connection;

    std::string checkVersion();
    int login();
};

#endif //MANAGER_GAME_HPP
