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

class Server
{
public:
    Server();
    int setup();
    int run();

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
    std::vector<std::thread> threads;
    std::vector<int> closed;
    std::mutex closedMutex;
    std::vector<Connection> connections;
    std::thread cleaner;

    void cleanup();

    /** 
     * Request Handlers
     * All handlers will take a string message and return a string response
     */
    static std::map<int, std::string (*)(Server &myself, std::string msg)> requestMap; 
    static std::string VersionCheckHandler(Server &myself, std::string msg);
    static std::string LoginHandler(Server &myself, std::string msg);
};

#endif //MANAGER_SERVER_HPP
