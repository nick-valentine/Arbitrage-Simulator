#include "Managers/Server.hpp"

const std::string Server::configWorldNameKey = "world_name";
const std::string Server::defaultWorldName = "world";

const std::string Server::configPortNumberKey = "server_port";
const int Server::defaultPortNumber = 9797;

Server::Server()
{
}

Server::~Server()
{
    for (int i = 0; i < this->sessions.size(); ++i) {
        if (this->sessions[i] != NULL) {
            delete this->sessions[i];
            this->sessions[i] = NULL;
        }
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
            int spot = this->firstFreeSpot();
            temp->init(this->world, this->version, spot);
            this->logger->info("Client: %i connected", spot);
            temp->setLogger(this->logger);
            temp->run();
            temp->addListener("session_close", this);
            temp->addListener("player_moved", this);
            temp->addListener("invalidate_players", this);
            this->sessions[spot] = temp;
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

int Server::firstFreeSpot()
{
    for (int i = 0; i < this->sessions.size(); ++i) {
        if (this->sessions[i] == NULL) {
            return i;
        }
    }
    this->sessions.push_back(NULL);
    return this->sessions.size() - 1;
}

void Server::act(std::string name, std::string value)
{
    this->logger->info("listened %s, %s", name.c_str(), value.c_str());
    if (name == "session_close") {
        this->cleanSessions();
    } else if(name == "player_moved") {
        this->logger->info("Player moved: %s", value.c_str());
        this->broadcastPlayerLocation(value);
    } else if(name == "invalidate_players") {
        this->logger->info("Players invalidated: %s", value.c_str());
        this->broadcastInvalidatePlayers();
    }
}

void Server::cleanSessions()
{
    for (int i = 0; i < this->sessions.size(); ++i) {
        if (this->sessions[i] != NULL) {
            if (this->sessions[i]->getState() == ServerSession::DISCONNECTED) {
                this->sessions[i]->cleanup();
                delete this->sessions[i];
                this->sessions[i] = NULL;
                this->logger->info("Client: %i disconnected", i);
            }
        }
    }
    this->broadcastInvalidatePlayers();
}

void Server::broadcastPlayerLocation(std::string value)
{
    std::stringstream ss;
    ss.str(value);
    int id;
    ss>>id;
    for (int i = 0; i < this->sessions.size(); ++i) {
        if (this->sessions[i] != NULL && i != id) {
            this->logger->info("Broadcasting: %s about %d to %d", value.c_str(), id, i);
            this->sessions[i]->write(ss.str());
        }
    }
}

void Server::broadcastInvalidatePlayers()
{
    this->logger->info("Broadcasting: players invalidated");
    std::string msg = "0 " + boost::lexical_cast<std::string>(ServerSession::PLAYER_INVALIDATE) + "\n";
    for (int i = 0; i < this->sessions.size(); ++i) {
        if (this->sessions[i] != NULL) {
            this->sessions[i]->write(msg);
        }
    }
}

