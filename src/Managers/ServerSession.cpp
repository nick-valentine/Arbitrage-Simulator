#include "Managers/ServerSession.hpp"

std::map<int, std::string (*)(ServerSession &myself, std::string msg)> ServerSession::requestMap = 
    {
        {ServerSession::VERSION_CHECK, VersionCheckHandler},
        {ServerSession::LOGIN, LoginHandler},
        {ServerSession::REQUEST_CHUNK, GetWorldChunkHandler},
    }; 

ServerSession::ServerSession()
{
    this->state = UNSET;
    this->version = "";
}

ServerSession::ServerSession(Connection conn)
{
    this->state = UNSET;
    this->version = "";
    this->setConnection(conn);
}

int ServerSession::init(world_ptr world, std::string version)
{
    this->world = world;
    this->version = version;
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
    return this->conn.write(msg);
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
                this->state = DISCONNECTED;
                return;
            }
        
        } catch(std::exception& e) {
            std::cerr<<e.what()<<std::endl;
            this->conn.close();
            this->state = DISCONNECTED;
            return;
        }
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
        myself.logger->debug("Client request versio check");
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

std::string ServerSession::LoginHandler(ServerSession &myself, std::string msg)
{
    int type;
    std::string username, password;
    std::stringstream ss;
    ss.str(msg);
    ss>>type>>username>>password;
    return "Welcome, " + username;
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
