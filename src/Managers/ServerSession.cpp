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
            std::cout<<"Reading"<<std::endl;
            std::string message = this->conn.read();
            std::cout<<message<<std::endl;
            std::stringstream ss;
            int request_type;
        
            ss.str(message);
            ss>>request_type;
            std::string response = boost::lexical_cast<std::string>(ERROR) + " invalid message" + Globals::network_message_delimiter;
            if (this->requestMap.find(request_type) != this->requestMap.end()) {
                response = this->requestMap[request_type](*this, message);
            }
            
            std::cout<<"Writing"<<std::endl;
            std::cout<<response<<std::endl;
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
    std::cout<<"Client request version check ";
    if (myself.version == version) {
        std::cout<<"version OK\n";
        myself.state = AUTHENTICATING; // continue to next state
        return boost::lexical_cast<std::string>(ServerSession::VERSION_CHECK_OK) + Globals::network_message_delimiter;
    } else {
        std::cout<<"version INCOMPATIBLE\n";
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
    std::cout<<"Client request chunk ("<<chunkY<<", "<<chunkX<<")"<<std::endl;
    ss.str("");

    ss<<ServerSession::REQUEST_OK<<" ";
    
    (*myself.world).getChunk(chunkY, chunkX).toStringStream(&ss);
    ss<<Globals::network_message_delimiter;

    return ss.str();
    
}