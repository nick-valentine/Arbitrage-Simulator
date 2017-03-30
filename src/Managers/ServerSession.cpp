#include "Managers/ServerSession.hpp"

std::map<int, std::string (*)(ServerSession &myself, std::string msg)> ServerSession::requestMap = 
    {
        {ServerSession::VERSION_CHECK, VersionCheckHandler},
        {ServerSession::LOGIN, LoginHandler}
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
            std::string response = boost::lexical_cast<std::string>(ERROR) + " invalid message";
            if (this->requestMap.find(request_type) != this->requestMap.end()) {
                response = this->requestMap[request_type](*this, message);
            }
            
            std::cout<<response<<std::endl;
            std::cout<<"Writing"<<std::endl;
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
        return boost::lexical_cast<std::string>(ServerSession::VERSION_CHECK_OK) + "\n";
    } else {
        std::cout<<"version INCOMPATIBLE\n";
        myself.state = DISCONNECTING; // flag to disconnect
        return boost::lexical_cast<std::string>(ServerSession::VERSION_INCOMPATIBLE) + 
            " " + 
            myself.version + 
            "\n"
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


