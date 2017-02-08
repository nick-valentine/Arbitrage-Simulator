#ifndef MANAGER_SERVER_HPP
#define MANAGER_SERVER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>

#include "Helpers/String.hpp"
#include "GameObjects/World.hpp"

using boost::asio::ip::tcp;

class Server
{
public:
    Server();
    int setup();
    int run();

    enum REQUST_TYPE {
        ERROR = 0,
        LOGIN = 1,
        REQUEST_CHARACTER = 2,
        REQUEST_WORLD = 3,
        REQUEST_CHUNK = 4,
        REQUEST_CITY = 5,
    };
private:
    static const std::string configWorldNameKey;
    static const std::string defaultWorldName;
    static const std::string configPortNumberKey;
    static const int defaultPortNumber;

    int portNumber;

    void configure();

    std::string read(tcp::socket &socket);

    /** 
     * Request Handlers
     * All handlers will take a string message and return a string response
     */
    static std::map<int, std::string (*)(std::string msg)> requestMap; 
    static std::string LoginHandler(std::string msg);
};

#endif //MANAGER_SERVER_HPP
