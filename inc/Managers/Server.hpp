#ifndef MANAGER_SERVER_HPP
#define MANAGER_SERVER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <chrono>
#include <thread>

#include "GameObjects/World.hpp"
#include "Managers/ServerSession.hpp"

using boost::asio::ip::tcp;

/**
 * Server Manager.
 * Dispatcher and manager for all server sessions. Owns and maintains world state.
 */
class Server
{
public:
    Server();
    ~Server();
    int setup();
    int run();

private:
    static const std::string configWorldNameKey;
    static const std::string defaultWorldName;
    static const std::string configPortNumberKey;
    static const int defaultPortNumber;
    static const int cleanupInterval;

    int portNumber;
    std::string version;

    void initialize();
    void configure();

    std::vector<ServerSession *> sessions;
    void cleanupSessions();
    std::thread cleaner;

    World world;
};

#endif //MANAGER_SERVER_HPP
