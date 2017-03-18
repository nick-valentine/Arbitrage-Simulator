#include "Managers/Server.hpp"

const std::string Server::configWorldNameKey = "world_name";
const std::string Server::defaultWorldName = "world";

const std::string Server::configPortNumberKey = "server_port";
const int Server::defaultPortNumber = 9797;

std::map<int, std::string (*)(Server &myself, std::string msg)> Server::requestMap = 
    {
        {Server::VERSION_CHECK, VersionCheckHandler},
        {Server::LOGIN, LoginHandler}
    }; 

Server::Server()
{

}

int Server::setup()
{
    this->configure();
    this->initialize();
    return 0;
}

int Server::run()
{
    using boost::asio::ip::tcp;
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), this->portNumber));
    while (true) {
        Connection::socket_ptr sock(new tcp::socket(io_service));
        int connectionIndex = this->connections.size();
        this->connections.push_back(Connection());
        this->connections[connectionIndex].bind(sock);
        acceptor.accept(*this->connections[connectionIndex].get());
        if (threads.size() < 32) {
            int threadIndex = this->threads.size();
            this->threads.push_back(std::thread(&Server::manageSession, this, connectionIndex, threadIndex));
        } else {
            std::cerr<<threads.size()<<" connections open already, connection denied"<<std::endl;
            this->connections[connectionIndex].close();
        }
    }
    return 0;
}

void Server::initialize()
{
    this->cleaner = std::thread(&Server::cleanup, this);
}

void Server::configure()
{
    ConfigLoader::load();

    this->portNumber = ConfigLoader::getIntOption(
        Server::configPortNumberKey,
        Server::defaultPortNumber
    );

    this->version = ConfigLoader::getVersion();

    this->world = World(
        ConfigLoader::getStringOption(
            Server::configWorldNameKey,
            Server::defaultWorldName
        )
    );
}

void Server::manageSession(int connectionIndex, int threadIndex)
{
    while (true) {
        try {
            std::string message = this->connections[connectionIndex].read();
            std::cout<<message<<std::endl;
            std::stringstream ss;
            int request_type;
        
            ss.str(message);
            ss>>request_type;
            std::string response = boost::lexical_cast<std::string>(ERROR) + " invalid message";
            if (this->requestMap.find(request_type) != this->requestMap.end()) {
                response = this->requestMap[request_type](*this, message);
            }
            
            std::cout<<response;
            this->connections[connectionIndex].write(response);
        
        } catch(std::exception& e) {
            std::cerr<<e.what()<<std::endl;
            this->connections[connectionIndex].close();
            this->connections[connectionIndex] = this->connections[this->connections.size() - 1];
            this->connections.pop_back();
            this->closed.push_back(threadIndex);
            return;
        }
    }
}

void Server::cleanup()
{
    while (true) {
        std::unique_lock<std::mutex> lock(closedMutex, std::try_to_lock);
        if(lock.owns_lock()) {
            for (int i = 0; i < this->closed.size(); ++i) {
                this->threads[this->closed[i]] = std::thread(std::move(this->threads[this->threads.size() - 1]));
                this->threads.pop_back();
            }
            this->closed.clear();
        } else {
            std::cerr<<"Lock on cleanup threads failed.";
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

std::string Server::VersionCheckHandler(Server &myself, std::string msg)
{
    int type;
    std::string version;
    std::stringstream ss;
    ss.str(msg);
    ss>>type>>version;
    std::cout<<"Client request version check ";
    if (myself.version == version) {
        std::cout<<"version OK\n";
        return boost::lexical_cast<std::string>(Server::VERSION_CHECK_OK) + "\n";
    } else {
        std::cout<<"version INCOMPATIBLE\n";
        return boost::lexical_cast<std::string>(Server::VERSION_INCOMPATIBLE) + 
            " " + 
            myself.version + 
            "\n"
        ;
    }
}

std::string Server::LoginHandler(Server &myself, std::string msg)
{
    int type;
    std::string username, password;
    std::stringstream ss;
    ss.str(msg);
    ss>>type>>username>>password;
    return "Welcome, " + username;
}
