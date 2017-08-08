#include "Managers/ServerSession.hpp"

const int ServerSession::tickrate = 8;

std::map<int, std::string (*)(ServerSession &myself, std::string msg)> ServerSession::requestMap = 
    {
        {ServerSession::VERSION_CHECK, VersionCheckHandler},
        {ServerSession::LOGIN, LoginHandler},
        {ServerSession::UPDATE, UpdateCheckHandler},
        {ServerSession::REQUEST_ITEM_MAP, GetItemMapHandler},
        {ServerSession::REQUEST_WORLD_DIMS, GetWorldDimensionsHandler},
        {ServerSession::QUIT, QuitHandler},
        {ServerSession::REQUEST_CHUNK, GetWorldChunkHandler},
        {ServerSession::REQUEST_PLAYER, GetPlayerHandler},
        {ServerSession::REQUEST_ALL_PLAYERS, GetAllPlayersHandler},
        {ServerSession::PLAYER_MOVE, PlayerMovedHandler},
    }; 

ServerSession::ServerSession()
{
    this->updates = std::queue<std::string>();
    this->state = UNSET;
    this->version = "";
    this->id = -1;
}

ServerSession::ServerSession(Connection conn)
{
    this->updates = std::queue<std::string>();
    this->state = UNSET;
    this->version = "";
    this->setConnection(conn);
    this->id = -1;
}

int ServerSession::init(world_ptr world, std::string version, int id)
{
    this->updates = std::queue<std::string>();
    this->world = world;
    this->version = version;
    this->id = id;
}

void ServerSession::setLogger(boost::shared_ptr<Logger> logger)
{
    this->logger = logger;
}

int ServerSession::run()
{
    this->thread = std::thread(&ServerSession::sessionLoop, this);
}

int ServerSession::cleanup()
{
    this->thread.join();
}

bool ServerSession::write(std::string msg)
{
    this->updates.push(msg);
}

void ServerSession::setConnection(Connection conn)
{
    this->conn = conn;
}

ServerSession::SESSION_STATE ServerSession::getState()
{
    return this->state;
}

void ServerSession::sessionLoop()
{
    this->state = HANDSHAKING;
    while (true) {
        try {
            this->readHandle();
        } catch(std::exception& e) {
            std::cerr<<e.what()<<std::endl;
            this->conn.close();
            this->notify(
                "session_close", 
                boost::lexical_cast<std::string>(this->id)
            );
            this->state = DISCONNECTED;
            return;
        }
    }

}

void ServerSession::readHandle()
{
    if (this->logger) {
        this->logger->debug("Reading");
    }
    std::string message = this->conn.read();
    if (this->logger) {
        this->logger->debug(message.c_str());
    }
    std::stringstream ss;
    int request_type;

    ss.str(message);
    ss>>request_type;
    std::string response = boost::lexical_cast<std::string>(ERROR) + " invalid message" + Globals::network_message_delimiter;
    if (this->requestMap.find(request_type) != this->requestMap.end()) {
        response = this->requestMap[request_type](*this, message);
    }
    
    if (this->logger) {
        this->logger->debug("Writing");
        this->logger->debug(response.c_str());
    }
    this->conn.write(response);

    if (state == DISCONNECTING) {
        this->conn.close();
        this->notify(
            "session_close", 
            boost::lexical_cast<std::string>(this->id)
        );
        this->state = DISCONNECTED;
        return;
    }
}

std::string ServerSession::VersionCheckHandler(ServerSession &myself, std::string msg)
{
    int type;
    std::string version;
    std::stringstream ss;
    ss.str(msg);
    ss>>type>>version;
    if (myself.logger) {
        myself.logger->debug("Client request version check");
    }
    if (myself.version == version) {
        if (myself.logger) {
            myself.logger->debug("Version OK");
        }
        myself.state = AUTHENTICATING; // continue to next state
        return boost::lexical_cast<std::string>(ServerSession::VERSION_CHECK_OK) + Globals::network_message_delimiter;
    } else {
        if (myself.logger) {
            myself.logger->debug("Version INCOMPATIBLE");
        }
        myself.state = DISCONNECTING; // flag to disconnect
        return boost::lexical_cast<std::string>(ServerSession::VERSION_INCOMPATIBLE) + 
            " " + 
            myself.version + 
            Globals::network_message_delimiter
        ;
    }
}

std::string ServerSession::UpdateCheckHandler(ServerSession &myself, std::string msg)
{
    std::string val = myself.updates.front();
    myself.updates.pop();
    return val;
}

std::string ServerSession::GetWorldDimensionsHandler(ServerSession &myself, std::string msg)
{
    unsigned int worldX = myself.world->getWorldWidth();
    unsigned int worldY = myself.world->getWorldHeight();
    int chunkX = myself.world->getChunkWidth();
    int chunkY = myself.world->getChunkHeight();
    return boost::lexical_cast<std::string>(worldX) + " " +
        boost::lexical_cast<std::string>(worldY) + " " +
        boost::lexical_cast<std::string>(chunkX) + " " +
        boost::lexical_cast<std::string>(chunkY) + "\n";
}

std::string ServerSession::LoginHandler(ServerSession &myself, std::string msg)
{
    int type;
    std::string username, password;
    std::stringstream ss;
    ss.str(msg);
    ss>>type>>username>>password;
    return "Welcome, " + username;
}

std::string ServerSession::GetItemMapHandler(ServerSession &myself, std::string msg)
{
    std::stringstream ss;
    ItemMap::toStringStream(&ss);
    return ss.str() + "\n";
}

std::string ServerSession::QuitHandler(ServerSession &myself, std::string msg)
{
    myself.state = DISCONNECTING;
    return "Goodbye\n";
}

std::string ServerSession::GetWorldChunkHandler(ServerSession &myself, std::string msg)
{
    int type, chunkY, chunkX;
    std::stringstream ss;
    ss.str(msg);
    ss>>type>>chunkY>>chunkX;
    if (myself.logger) {
        myself.logger->debug(
            "Client request chunk (%d, %d)",
            chunkY,
            chunkX
        );
    }
    ss.str("");

    ss<<ServerSession::REQUEST_OK<<" ";
    
    if ((*myself.world).chunkInWorld(chunkY, chunkX)) {
        (*myself.world).getChunk(chunkY, chunkX).toStringStream(&ss);
    } else {
        ss<<boost::lexical_cast<std::string>(ServerSession::ERROR);
        myself.logger->debug("Invalid chunk requested");
    }
    ss<<Globals::network_message_delimiter;

    return ss.str();
}

std::string ServerSession::GetPlayerHandler(ServerSession &myself, std::string msg)
{
    std::stringstream ss;
    ss.str(msg);
    int type;
    std::string name;
    ss>>type>>name;
    int index = myself.world->getPlayer(name);
    ss<<index<<Globals::network_message_delimiter;
    return ss.str();
}

std::string ServerSession::GetAllPlayersHandler(ServerSession &myself, std::string msg)
{
    std::stringstream ss;
    myself.world->playersToStringstream(&ss);
    return ss.str() + Globals::network_message_delimiter;
}

std::string ServerSession::PlayerMovedHandler(ServerSession &myself, std::string msg)
{
    std::stringstream ss;
    ss.str(msg);
    int type, index, posY, posX;
    ss>>type>>index>>posY>>posX;
    if (myself.logger) {
        myself.logger->debug(
            "Player %d moved (%d, %d)",
            index,
            posY,
            posX
        );
    }
    myself.notify("player_moved", boost::lexical_cast<std::string>(myself.id) + " " + msg);
    myself.world->movePlayer(index, posY, posX);
    ss<<ServerSession::REQUEST_OK<<Globals::network_message_delimiter;
    return ss.str();
}
