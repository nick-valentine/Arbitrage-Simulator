#include "Managers/Server.hpp"

const std::string Server::configWorldNameKey = "world_name";
const std::string Server::defaultWorldName = "world";

const std::string Server::configPortNumberKey = "server_port";
const int Server::defaultPortNumber = 9797;

std::map<int, std::string (*)(std::string msg)> Server::requestMap = 
    {
        {Server::LOGIN, LoginHandler}
    }; 

Server::Server()
{

}

int Server::setup()
{
    this->configure();
    return 0;
}

int Server::run()
{
    using boost::asio::ip::tcp;
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), this->portNumber));
    while (true) {
        tcp::socket socket(io_service);
        
        acceptor.accept(socket);
        try {
            std::string message = this->read(socket);
            std::cout<<message<<std::endl;
            std::stringstream ss;
            int request_type;

            ss.str(message);
            ss>>request_type;
            std::string response = boost::lexical_cast<std::string>(ERROR) + " invalid message";
            if (this->requestMap.find(request_type) != this->requestMap.end()) {
                response = this->requestMap[request_type](message);
            }
            
            std::cout<<response;
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(response), ignored_error);

        } catch(std::exception& e) {
            std::cerr<<e.what()<<std::endl;
        }
    
    }
    return 0;
}

void Server::configure()
{
    ConfigLoader::load();

    this->portNumber = ConfigLoader::getIntOption(
        Server::configPortNumberKey,
        Server::defaultPortNumber
    );

//    this->world = World(
//        ConfigLoader::getStringOption(
//            Server::configWorldNameKey,
//            Server::defaultWorldName
//        )
//    );
}

std::string Server::read(tcp::socket &socket)
{
    boost::system::error_code error;
    boost::asio::streambuf sb;
    std::size_t len = boost::asio::read_until(socket, sb, "\n",error);
    std::string buff;
    buff.resize(len);
    sb.sgetn(&buff[0], buff.size());

    if (error) {
        throw boost::system::system_error(error);
    }

    return buff;
}

std::string Server::LoginHandler(std::string msg)
{
    int type;
    std::string username, password;
    std::stringstream ss;
    ss.str(msg);
    ss>>type>>username>>password;
    return "Welcome, " + username;
}
