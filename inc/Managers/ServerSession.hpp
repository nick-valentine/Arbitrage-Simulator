#ifndef SERVER_SESSION_HPP
#define SERVER_SESSION_HPP

#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

#include "Globals.hpp"
#include "Networking/Connection.hpp"
#include "Services/WorldInteraction/LocalWorldInteraction.hpp"

using boost::asio::ip::tcp;

/**
 * Server Session.
 * Manager for server/client communication.
 */
class ServerSession
{
public:
    typedef boost::shared_ptr<LocalWorldInteraction> world_ptr;

    /**
     * Request Type.
     * An enumeration of all possible requests a client can make, or responses
     * a server can return.
     */
    enum REQUST_TYPE {
        ERROR = 0,
        REQUEST_OK = 1,
        VERSION_CHECK = 10,
        VERSION_CHECK_OK = 12,
        VERSION_INCOMPATIBLE = 13,
        LOGIN = 20,
        REQUEST_CHARACTER = 100,
        REQUEST_WORLD = 110,
        REQUEST_CHUNK = 120,
        REQUEST_CITY = 130,
    };

    enum SESSION_STATE {
        UNSET = 5,
        HANDSHAKING = 10,
        AUTHENTICATING = 20,
        PLAYING = 30,
        DISCONNECTING = 40,
        DISCONNECTED = 41
    };

    ServerSession();
    ServerSession(Connection conn);
    int init(world_ptr world, std::string version);

    /**
     * Launch thread to manage this session.
     */
    int run();

    /**
     * Join threads and do work to end this session.
     */
    int cleanup();

    /**
     * Wrapper for connection write.
     * Allow for owner to write direcly to this connection.
     *
     * @param  std::string msg
     * @return bool success
     */
    bool write(std::string msg);

    void setConnection(Connection conn);

    SESSION_STATE getState();
private:
    SESSION_STATE state;
    std::string version;
    std::thread thread;
    Connection conn;
    world_ptr world;

    void sessionLoop();

    /** 
     * Request Handlers.
     * All handlers will take a string message and return a string response
     */
    static std::map<int, std::string (*)(ServerSession &myself, std::string msg)> requestMap; 

    /**
     * Request Handler: Version Check.
     * Handle a request to check the compatibility of this server and a client.
     *
     * @param  ServerSession &myself
     * @param  std::string msg the message the client sent
     * @return std::string the response
     */
    static std::string VersionCheckHandler(ServerSession &myself, std::string msg);

    /**
     * Request Handler: Login Handler
     * Check for existing user with same username and password, if match then
     * this session may use that users character. Otherwise, deny access.
     *
     * @param  ServerSession &myself
     * @param  std::string msg the message the client sent
     * @return std::string the response
     */
    static std::string LoginHandler(ServerSession &myself, std::string msg);

    /**
     * Request Handler: Get World Chunk.
     * Get the world chunk at the Y, X coordinates requested by the client and
     * return it.
     *
     * @param  ServerSession &myself
     * @param  std::string msg the message the client sent
     * @return std::string the response
     */
    static std::string GetWorldChunkHandler(ServerSession &myself, std::string msg);

};

#endif //SERVER_SESSION_HPP
