#include "Services/WorldInteraction/NetworkedWorldInteraction.hpp"

NetworkedWorldInteraction::NetworkedWorldInteraction(std::string server, std::string port) : LocalWorldInteraction("NetworkedWorld")
{
    this->connected = true;
    if (!this->connection.connect(server, port)) {
        this->connected = false;
    }
    this->configure();
    this->playerY = 0;
    this->playerX = 0;
    this->chunksLoaded = std::vector< std::pair<int, int> >();
}

bool NetworkedWorldInteraction::loadWorld(boost::shared_ptr<Logger> logger)
{
    this->logger = logger;
    if (!this->connected) {
        return false;
    }
    if (!this->handShake()) {
        logger->warn("Could not connect to server");
        return false;
    }
    this->getMetadata();

    return true;
}

void NetworkedWorldInteraction::cleanup()
{
    this->logger->info("Quitting");
    this->quit();
}

void NetworkedWorldInteraction::draw(Window::window_ptr window)
{
    this->draw(window, playerY, playerX);
}

void NetworkedWorldInteraction::draw(Window::window_ptr window, int playerY, int playerX)
{
    for (int i = 0; i < this->chunks.size(); ++i) {
        for (int j = 0; j < this->chunks[i].size(); ++j) {
            if (this->hasChunkLoaded(i, j)) {
                this->chunks[i][j].draw(window, playerY, playerX);
            }
        }
    }
}

void NetworkedWorldInteraction::movePlayerToCoordinate(int y, int x)
{
    this->playerY = y;
    this->playerX = x;

    int chunkX, chunkY, localX, localY;
    this->playerCoordinatesToChunkCoordinates(chunkY, chunkX, localY, localX);
    for (int i = chunkY-1; i <= chunkY+1; ++i) {
        for (int j = chunkX-1; j <= chunkX+1; ++j) {
            if (
                this->chunkInWorld(i,j) &&
                !this->hasChunkLoaded(i, j)
            ) {
                this->fetchChunk(i, j);
            }
        }
    }
}

City NetworkedWorldInteraction::getCity(int y, int x)
{
    int chunkY, chunkX, localY, localX;
    this->globalCoordinatesToChunkCoordinates(
        y, x,
        chunkY, chunkX,
        localY, localX
    );
    if (!this->hasChunkLoaded(chunkY, chunkX)) {
        this->fetchChunk(chunkY, chunkX);
    }
    return this->chunks[chunkY][chunkX].getCity(localY, localX);
}

void NetworkedWorldInteraction::configure()
{
    ConfigLoader::load(); 
    this->version = ConfigLoader::getVersion();
}

bool NetworkedWorldInteraction::hasChunkLoaded(int y, int x)
{
    for (int i = 0; i < this->chunksLoaded.size(); ++i) {
        if (chunksLoaded[i].first == y && chunksLoaded[i].second == x) {
            return true;
        }
    }
    return false;
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

void NetworkedWorldInteraction::getMetadata()
{
    std::string message = boost::lexical_cast<std::string>(ServerSession::REQUEST_ITEM_MAP) + "\n";
    this->connection.write(message);
    std::string response = this->connection.read();
    std::stringstream ss;
    ss.str(response);
    ItemMap::fromStringStream(&ss);

    message = boost::lexical_cast<std::string>(ServerSession::REQUEST_WORLD_DIMS) + "\n";
    this->connection.write(message);
    response = this->connection.read();
    ss.str(std::string());
    int worldX, worldY, chunkX, chunkY;
    ss.str(response);
    ss>>World::worldWidth
        >>World::worldHeight
        >>this->chunkWidth
        >>this->chunkHeight
    ;
}

std::string NetworkedWorldInteraction::checkVersion()
{
    std::string message = boost::lexical_cast<std::string>(ServerSession::VERSION_CHECK) + " " + this->version + "\n";
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
    this->connection.write(message);
    return 1;
}

void NetworkedWorldInteraction::quit()
{
    try {
        std::string message = boost::lexical_cast<std::string>(ServerSession::QUIT) + "\n";
        this->connection.write(message);
        std::string response = this->connection.read();
    } catch (boost::system::system_error& e) {
    }
}

int NetworkedWorldInteraction::fetchChunk(int chunkY, int chunkX)
{
    std::string message = 
        boost::lexical_cast<std::string>(ServerSession::REQUEST_CHUNK) + " " + 
        boost::lexical_cast<std::string>(chunkY) + " " + 
        boost::lexical_cast<std::string>(chunkX) + "\n"
    ;
    this->connection.write(message);
    std::string response = this->connection.read();
    std::stringstream ss;
    ss.str(response);
    int responseType;
    ss>>responseType;
    if (responseType == ServerSession::REQUEST_OK) {
        this->chunks.resize(
            std::max(
                int(this->chunks.size()), 
                chunkY + 1
            )
        );
        this->chunks[chunkY].resize(
            std::max(
                int(this->chunks[chunkY].size()), 
                chunkX + 1
            )
        );
        this->chunks[chunkY][chunkX].fromStringStream(&ss);
        this->chunksLoaded.push_back(std::pair<int, int>(chunkY, chunkX));
    }
}
