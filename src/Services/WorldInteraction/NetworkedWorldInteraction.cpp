#include "Services/WorldInteraction/NetworkedWorldInteraction.hpp"


NetworkedWorldInteraction::NetworkedWorldInteraction(std::string server, std::string port) : LocalWorldInteraction("NetworkedWorld")
{
    this->connected = true;
    if (!this->connection.connect(server, port)) {
        this->connected = false;
    }
    this->configure();
    this->chunksLoaded = std::vector< std::pair<int, int> >();
}

bool NetworkedWorldInteraction::loadWorld(boost::shared_ptr<Logger> logger)
{
    this->requestMap = std::map<int, void (*)(NetworkedWorldInteraction &myself, std::string msg)>();
    this->requestMap[ServerSession::PLAYER_MOVE] = NetworkedWorldInteraction::PlayerMovedHandler;

    this->logger = logger;
    if (!this->connected) {
        return false;
    }
    if (!this->handShake()) {
        logger->warn("Could not connect to server");
        return false;
    }
    this->getMetadata();
    this->getAllPlayers();

    this->updateFetcher = std::thread(&NetworkedWorldInteraction::updateLoop, this);

    return true;
}

void NetworkedWorldInteraction::cleanup()
{
    this->updateFetcher.join();
    this->logger->info("Quitting");
    this->quit();
}

void NetworkedWorldInteraction::movePlayer(int index, int y, int x)
{
    LocalWorldInteraction::movePlayer(index, y, x);

    std::string msg = boost::lexical_cast<std::string>(ServerSession::PLAYER_MOVE) + " " +
        boost::lexical_cast<std::string>(index) + " " +
        boost::lexical_cast<std::string>(y) + " " +
        boost::lexical_cast<std::string>(x) + "\n";
    msg = this->connection.writeRead(msg);
    std::stringstream ss;
    ss.str(msg);
    int response;
    ss>>response;
    if (response != ServerSession::REQUEST_OK) {
        this->logger->warn("Server did not acknowlege your movement");
    }


    int chunkX, chunkY, localX, localY;
    this->playerCoordinatesToChunkCoordinates(index, chunkY, chunkX, localY, localX);
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

Tile NetworkedWorldInteraction::getTileUnderPlayer(int index)
{
    int chunkY, chunkX, localY, localX;
    this->playerCoordinatesToChunkCoordinates(index, chunkY, chunkX, localY, localX);
    return this->getTile(chunkY, chunkX, localY, localX);
}

Tile NetworkedWorldInteraction::getTile(int chunkY, int chunkX, int localY, int localX)
{
    if (this->chunkInWorld(chunkY,chunkX)) {
        if (!this->hasChunkLoaded(chunkY, chunkX)) {
            this->fetchChunk(chunkY, chunkX);
        }
        return LocalWorldInteraction::getTile(chunkY, chunkX, localY, localX);
    }
    return Tile();
}

int NetworkedWorldInteraction::getPlayer(std::string name)
{
    std::string msg = boost::lexical_cast<std::string>(ServerSession::REQUEST_PLAYER) + " " + 
        name + "\n";
    msg = this->connection.writeRead(msg);
    std::stringstream ss;
    int player;
    ss.str(msg);
    ss>>player;
    this->logger->info("Player fetched: %i", player);
    return player;
}

void NetworkedWorldInteraction::getAllPlayers()
{
    std::string msg = boost::lexical_cast<std::string>(ServerSession::REQUEST_ALL_PLAYERS) + "\n";
    msg = this->connection.writeRead(msg);
    std::stringstream ss;
    ss.str(msg);
    this->playersFromStringstream(&ss);
}

std::string NetworkedWorldInteraction::getUpdates()
{
    std::string msg = boost::lexical_cast<std::string>(ServerSession::UPDATE) + "\n";
    msg = this->connection.writeRead(msg);
    if (msg[0] != '\n') {
        this->logger->info("%s", msg.c_str());
    }
    return msg;
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

void NetworkedWorldInteraction::silentMovePlayer(int index, int y, int x)
{
    this->logger->info("Player %d moved to %d, %d", index, y, x);
    this->players[index].move(y, x);
}

void NetworkedWorldInteraction::updateLoop()
{
    while (true) {
        std::string msg = this->getUpdates();
        this->updateHandler(msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(ServerSession::tickrate));
    }
}

void NetworkedWorldInteraction::updateHandler(std::string update)
{
    this->logger->info("%s", update.c_str());
    std::stringstream ss;
    int requestor, request_type;

    ss.str(update);
    ss>>requestor>>request_type;
    if (this->requestMap.find(request_type) != this->requestMap.end()) {
        this->requestMap[request_type](*this, update);
    }
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

void NetworkedWorldInteraction::PlayerMovedHandler(NetworkedWorldInteraction &myself, std::string msg)
{
    myself.logger->info("Executing player moved handler");
    int sender, type, who, y, x;
    std::stringstream ss;
    ss.str(msg);
    ss>>sender>>type>>who>>y>>x;

    myself.silentMovePlayer(who, y, x);
}

bool NetworkedWorldInteraction::handShake()
{
    std::string sVersion;
    if ("" == (sVersion = this->checkVersion())) {
        //Version OK, good to continue
        return true;
    } else {
        std::cerr<<"Your version does not match the servers.\nYou are running "<<
            this->version<<
            ".\n The server is running "<<
            sVersion
        ;
        return false;
    }
    return true;
}

void NetworkedWorldInteraction::getMetadata()
{
    std::string message = boost::lexical_cast<std::string>(ServerSession::REQUEST_ITEM_MAP) + "\n";
    std::string response = this->connection.writeRead(message);
    std::stringstream ss;
    ss.str(response);
    ItemMap::fromStringStream(&ss);

    message = boost::lexical_cast<std::string>(ServerSession::REQUEST_WORLD_DIMS) + "\n";
    response = this->connection.writeRead(message);
    ss.str(std::string());
    int worldX, worldY, chunkX, chunkY;
    ss.str(response);
    ss>>World::worldWidth
        >>World::worldHeight
        >>this->chunkWidth
        >>this->chunkHeight
    ;
    WorldChunk::setChunkWidth(this->chunkWidth);
    WorldChunk::setChunkHeight(this->chunkHeight);
}

std::string NetworkedWorldInteraction::checkVersion()
{
    std::string message = boost::lexical_cast<std::string>(ServerSession::VERSION_CHECK) + " " + this->version + "\n";
    this->logger->info("%s", message.c_str());
    std::string response = this->connection.writeRead(message);
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
        std::string response = this->connection.writeRead(message);
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
    std::string response = this->connection.writeRead(message);
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
