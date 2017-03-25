#ifndef MANAGER_SERVER_HPP
#define MANAGER_SERVER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>

#include "Helpers/String.hpp"
#include "GameObjects/World.hpp"
#include "Networking/Connection.hpp"

using boost::asio::ip::tcp;

/**
 * Server Manager.
 * Dispatcher and manager for all server sessions. Owns and maintains world state.
 */
class Server
{
public:
    Server();
    int setup();
    int run();

    /**
     * Request Type.
     * An enumeration of all possible requests a client can make, or responses
     * a server can return.
     */
    enum REQUST_TYPE {
        ERROR = 0,
        VERSION_CHECK = 1,
        VERSION_CHECK_OK = 2,
        VERSION_INCOMPATIBLE = 3,
        LOGIN = 10,
        REQUEST_CHARACTER = 100,
        REQUEST_WORLD = 110,
        REQUEST_CHUNK = 120,
        REQUEST_CITY = 130,
    };
private:
    static const std::string configWorldNameKey;
    static const std::string defaultWorldName;
    static const std::string configPortNumberKey;
    static const int defaultPortNumber;

    int portNumber;
    std::string version;

    void initialize();
    void configure();

    void manageSession(int connectionIndex, int threadIndex);

    World world;
    //@todo: the current method of managing connections/threads won't work for more than one person.
    std::vector<std::thread> threads;
    std::vector<int> closed;
    std::mutex closedMutex;
    std::vector<Connection> connections;
    std::thread cleaner;

    void cleanup();

    /** 
     * Request Handlers.
     * All handlers will take a string message and return a string response
     */
    static std::map<int, std::string (*)(Server &myself, std::string msg)> requestMap; 

    /**
     * Request Handler: Version Check.
     * Handle a request to check the compatibility of this server and a client.
     *
     * @param  Server &myself
     * @param  std::string msg the message the client sent
     * @return std::string the response
     */
    static std::string VersionCheckHandler(Server &myself, std::string msg);

    /**
     * Request Handler: Login Handler
     * Check for existing user with same username and password, if match then
     * this session may use that users character. Otherwise, deny access.
     *
     * @param  Server &myself
     * @param  std::string msg the message the client sent
     * @return std::string the response
     */
    static std::string LoginHandler(Server &myself, std::string msg);
};

#endif //MANAGER_SERVER_HPP
