#include "Services/WorldInteraction/NetworkedWorldInteraction.hpp"

NetworkedWorldInteraction::NetworkedWorldInteraction(std::string server, std::string port) : LocalWorldInteraction("NetworkedWorld")
{
    this->connection.connect(server, port);
    this->configure();
    this->playerY = 0;
    this->playerX = 0;
}

void NetworkedWorldInteraction::loadWorld()
{
    if (!this->handShake()) {
        std::cerr<<"Could not connect to server";
        exit(1);
    }
    this->generateWorld();
}

void NetworkedWorldInteraction::draw(Screen &screen)
{
    World::draw(screen, playerY, playerX);
}

void NetworkedWorldInteraction::movePlayerToCoordinate(int y, int x)
{
    this->playerY = y;
    this->playerX = x;
}

void NetworkedWorldInteraction::configure()
{
    ConfigLoader::load(); 
    this->version = ConfigLoader::getVersion();
}

bool NetworkedWorldInteraction::handShake()
{
    std::string sVersion;
    if ("" == (sVersion = this->checkVersion())) {
        //Version OK, good to continue
        return true;
    } else {
        std::cerr<<"Your version does not match the servers.\nYou are running " +
            this->version +
            ".\n The server is running " +
            sVersion
        ;
        return false;
    }
    return true;
}

std::string NetworkedWorldInteraction::checkVersion()
{
    std::string message = boost::lexical_cast<std::string>(ServerSession::VERSION_CHECK) + " " + this->version + "\n";
    std::cerr<<message;
    this->connection.write(message);
    std::string response = this->connection.read();
    std::stringstream ss;

    ss.str(response);
    int responseType;
    ss>>responseType;
    if (responseType == ServerSession::VERSION_CHECK_OK) {
        return "";
    } else if (responseType == ServerSession::VERSION_INCOMPATIBLE) {
        std::string serverVersion;
        ss>>serverVersion;
        return serverVersion;
    }
}

int NetworkedWorldInteraction::login()
{
    std::string message = boost::lexical_cast<std::string>(ServerSession::LOGIN) + " Username Password\n";
    std::cerr<<message;
    this->connection.write(message);
}
