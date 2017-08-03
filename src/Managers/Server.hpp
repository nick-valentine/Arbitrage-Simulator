#ifndef MANAGER_SERVER_HPP
#define MANAGER_SERVER_HPP

#include <string>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/shared_ptr.hpp>
#include <sstream>
#include <map>
#include <chrono>
#include <thread>

#include "Services/Logger/Logger.hpp"
#include "Services/Logger/ConsoleLogger.hpp"
#include "Services/WorldInteraction/LocalWorldInteraction.hpp"
#include "GameObjects/ItemMap.hpp"
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

    boost::shared_ptr<Logger> logger;

    int portNumber;
    std::string version;
    std::string worldName;

    void initialize();
    void configure();

    boost::ptr_vector<ServerSession> sessions;
    void cleanupSessions();
    std::thread cleaner;

    ServerSession::world_ptr world;
};

#endif //MANAGER_SERVER_HPP
