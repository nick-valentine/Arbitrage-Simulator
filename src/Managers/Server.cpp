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
            temp->init(this->world, this->version);
            temp->setLogger(this->logger);
            temp->run();
            this->sessions.push_back(temp);
        } else {
            this->logger->warn(
                "%d connections open already, connection denied",
                this->sessions.size()
            );
            conn.close();
        }
    }
    return 0;
}

void Server::initialize()
{
    this->logger = boost::shared_ptr<Logger>(new ConsoleLogger());

    this->cleaner = std::thread(&Server::cleanupSessions, this);

    ItemMap::init(this->logger);

    this->world = ServerSession::world_ptr(
        new LocalWorldInteraction(this->worldName)
    );

    (*this->world).loadWorld(this->logger);
}

void Server::configure()
{
    ConfigLoader::load();

    //@todo: abstract configuration out to a common point between Client and Server
    WorldChunk::configure();
    World::configure();
    City::load_city_names();

    this->portNumber = ConfigLoader::getIntOption(
        Server::configPortNumberKey,
        Server::defaultPortNumber
    );

    this->version = ConfigLoader::getVersion();
    this->worldName = ConfigLoader::getStringOption(
        Server::configWorldNameKey,
        Server::defaultWorldName
    );

}

void Server::cleanupSessions()
{
    while (true) {
        auto i = std::begin(this->sessions);
        this->logger->info(
            "Beginning session cleanup. %d sessions currently exist.",
            this->sessions.size()
        );
        while (i != std::end(this->sessions)) {
            if ((*i).getState() == ServerSession::DISCONNECTED) {
                (*i).cleanup();
                i = this->sessions.erase(i);
            } else {
                ++i;
            }
        }
        this->logger->info(
            "Finished session cleanup. %d sessions currently exist.",
            this->sessions.size()
        );
        std::this_thread::sleep_for(std::chrono::seconds(Server::cleanupInterval));
    }
}
