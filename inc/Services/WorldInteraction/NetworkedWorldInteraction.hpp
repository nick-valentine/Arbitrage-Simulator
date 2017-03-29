#ifndef NETWORKED_WORLD_INTERACTION
#define NETWORKED_WORLD_INTERACTION

#include <string>
#include <iostream>
#include <stdlib.h>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

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
    void movePlayerToCoordinate(int y, int x);
private:
    std::string version;
    void configure();

    Connection connection;

    bool handShake();

    std::string checkVersion();
    int login();
};

#endif //NETWORKED_WORLD_INTERACTION
