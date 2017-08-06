#ifndef NETWORKED_WORLD_INTERACTION
#define NETWORKED_WORLD_INTERACTION

#include <algorithm>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <utility>
#include <boost/shared_ptr.hpp>

#include "ConfigLoader.hpp"
#include "GameObjects/World.hpp"
#include "GameObjects/ItemMap.hpp"
#include "Managers/ServerSession.hpp"
#include "Networking/Connection.hpp"
#include "Window/Window.hpp"
#include "Services/WorldInteraction/LocalWorldInteraction.hpp"
#include "Services/WorldInteraction/WorldInteractionInterface.hpp"
#include "Services/Logger/Logger.hpp"

using boost::asio::ip::tcp;

/**
 * Manager for networked world interaction.
 *
 * @TODO: implement more graceful error handling
 * @TODO: send player movement notices to server
 * @TODO: fetch city objects from server
 */
class NetworkedWorldInteraction : virtual public WorldInteractionInterface, private LocalWorldInteraction
{
public:
    NetworkedWorldInteraction(std::string server, std::string port);

    bool loadWorld(boost::shared_ptr<Logger> logger);
    void cleanup();
    void draw(Window::window_ptr window);
    void draw(Window::window_ptr window, int playerY, int playerX);
    void movePlayerToCoordinate(int y, int x);

    City getCity(int y, int x);
private:
    std::string version;
    std::vector< std::pair<int, int> > chunksLoaded;

    void configure();

    bool hasChunkLoaded(int y, int x);

    Connection connection;
    bool connected;
    Logger::LoggerPtr logger;

    bool handShake();
    void getMetadata();

    std::string checkVersion();
    int login();
    void quit();
    int fetchChunk(int chunkY, int chunkX);
};

#endif //NETWORKED_WORLD_INTERACTION
