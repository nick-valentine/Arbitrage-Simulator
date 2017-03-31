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

#include "ConfigLoader.hpp"
#include "GameObjects/World.hpp"
#include "Managers/ServerSession.hpp"
#include "Networking/Connection.hpp"
#include "Screen.hpp"
#include "Services/WorldInteraction/LocalWorldInteraction.hpp"
#include "Services/WorldInteraction/WorldInteractionInterface.hpp"

using boost::asio::ip::tcp;

/**
 * Manager for networked world interaction.
 *
 * @TODO: implement more graceful error handling
 * @TODO: fetch world & worldChunk sizes from server
 * @TODO: fetch worldChunks from server
 * @TODO: send player movement notices to server
 * @TODO: fetch city objects from server
 */
class NetworkedWorldInteraction : virtual public WorldInteractionInterface, private LocalWorldInteraction
{
public:
    NetworkedWorldInteraction(std::string server, std::string port);

    void loadWorld();
    void draw(Screen &screen);
    void draw(Screen &screen, int playerY, int playerX);
    void movePlayerToCoordinate(int y, int x);
private:
    std::string version;
    std::vector< std::pair<int, int> > chunksLoaded;

    void configure();

    bool hasChunkLoaded(int y, int x);

    Connection connection;

    bool handShake();

    std::string checkVersion();
    int login();
    int fetchChunk(int chunkY, int chunkX);
};

#endif //NETWORKED_WORLD_INTERACTION
