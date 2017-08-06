#ifndef SERVER_SESSION_HPP
#define SERVER_SESSION_HPP

#include <stdio.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

#include "Globals.hpp"
#include "EventNotifier.hpp"
#include "Networking/Connection.hpp"
#include "Services/Logger/Logger.hpp"
#include "Services/WorldInteraction/LocalWorldInteraction.hpp"

using boost::asio::ip::tcp;

/**
 * Server Session.
 * Manager for server/client communication.
 */
class ServerSession : public Notifier
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
        QUIT = 1,
        REQUEST_OK = 2,
        VERSION_CHECK = 10,
        VERSION_CHECK_OK = 12,
        VERSION_INCOMPATIBLE = 13,
        LOGIN = 20,
        REQUEST_CHARACTER = 100,
        REQUEST_WORLD_DIMS = 110,
        REQUEST_CHUNK = 120,
        REQUEST_CITY = 130,
        REQUEST_ITEM_MAP = 140,
        REQUEST_PLAYER = 150,
        REQUEST_ALL_PLAYERS = 160,
        PLAYER_MOVE = 170
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
    int init(world_ptr world, std::string version, int id);
    void setLogger(boost::shared_ptr<Logger> logger);

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
    int id;
    Connection conn;
    world_ptr world;

    boost::shared_ptr<Logger> logger;

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
     * Request Handler: GetWorldDimenstions
     * Sends the server's world size and world chunk size
     *
     * @param  ServerSession &myself
     * @param  std::string msg the message the client sent
     * @return std::string the response
     */
    static std::string GetWorldDimensionsHandler(ServerSession &myself, std::string msg);

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
     * Request Handler: Get ItemMap
     * Get the server's item map, so that all clients will match
     *
     * @param  ServerSession &myself
     * @param  std::string msg the message the client sent
     * @return std::string the response
     */
    static std::string GetItemMapHandler(ServerSession &myself, std::string msg);

    /**
     * Request Handler: Quit Handler
     * Disconnects from the client
     *
     * @param  ServerSession &myself
     * @param  std::string msg the message the client sent
     * @return std::string the response
     */
    static std::string QuitHandler(ServerSession &myself, std::string msg);

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


    /**
     * Request Handler: Get Player
     * Gets a player with given name if one exists, otherwise provides a new player
     *
     * @param  ServerSession &myself
     * @param  std::string msg the message the client sent
     * @return std::string the response
     */
    static std::string GetPlayerHandler(ServerSession &myself, std::string msg);

    /**
     * Request Handler: Get All Player
     * Get all players connected to this server
     *
     * @param  ServerSession &myself
     * @param  std::string msg the message the client sent
     * @return std::string the response
     */
    static std::string GetAllPlayersHandler(ServerSession &myself, std::string msg);

    /**
     * Request Handler: Player has moved
     * Recieves new location of the player in order to replicate it to all
     * other clients
     *
     * @param  ServerSession &myself
     * @param  std::string msg the message the client sent
     * @return std::string the response
     */
    static std::string PlayerMovedHandler(ServerSession &myself, std::string msg);
};

#endif //SERVER_SESSION_HPP
