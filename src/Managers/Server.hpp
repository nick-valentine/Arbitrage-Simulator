#ifndef MANAGER_SERVER_HPP
#define MANAGER_SERVER_HPP

#include <string>
#include <boost/shared_ptr.hpp>
#include <sstream>
#include <map>
#include <chrono>
#include <thread>
#include <vector>

#include "EventNotifier.hpp"
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
class Server : public Listener
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

    boost::shared_ptr<Logger> logger;

    int portNumber;
    std::string version;
    std::string worldName;

    void initialize();
    void configure();

    int firstFreeSpot();

    void act(int i);

    std::vector<ServerSession*> sessions;

    ServerSession::world_ptr world;
};

#endif //MANAGER_SERVER_HPP
