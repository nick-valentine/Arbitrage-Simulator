#include "Managers/Server.hpp"

const std::string Server::configWorldNameKey = "world_name";
const std::string Server::defaultWorldName = "world";

const std::string Server::configPortNumberKey = "server_port";
const int Server::defaultPortNumber = 9797;
const int Server::cleanupInterval = 10; //seconds

Server::Server()
{

}

Server::~Server()
{
    auto i = std::begin(this->sessions);
    while (i != std::end(this->sessions)) {
        delete *i;
    }
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
        Connection conn;
        conn.bind(sock);

        acceptor.accept(*conn.get());
        if (this->sessions.size() < 32) {
            ServerSession *temp = new ServerSession(conn);
            temp->init(this->version);
            temp->run();
            this->sessions.push_back(temp);
        } else {
            std::cerr<<this->sessions.size()<<" connections open already, connection denied"<<std::endl;
            conn.close();
        }
    }
    return 0;
}

void Server::initialize()
{
    this->cleaner = std::thread(&Server::cleanupSessions, this);
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

void Server::cleanupSessions()
{
    auto i = std::begin(this->sessions);
    while (i != std::end(this->sessions)) {
        if ((*i)->getState() == ServerSession::DISCONNECTED) {
            delete *i;
            i = this->sessions.erase(i);
        } else {
            ++i;
        }
    }
    std::this_thread::sleep_for(std::chrono::seconds(Server::cleanupInterval));
}
