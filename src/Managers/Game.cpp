#include "Managers/Game.hpp"

const std::string Game::configWorldNameKey = "world_name";
const std::string Game::defaultWorldName = "world";

Game::Game()
{

}

int Game::setup()
{
    this->configure();

    this->camera = Camera(0, 0);
    this->screen = Screen();

    this->player = Player("Bob", 0, 0);

    this->world.generateWorld();

    return 0;
}

int Game::run()
{
    try {
        this->connection.connect("localhost", "9797");

        std::string sVersion;
        if ("" == (sVersion = this->checkVersion())) {
            std::cerr<<"Version OK, good to continue\n";
        } else {
            std::cerr<<"Your version does not match the servers.\nYou are running " +
                this->version +
                ".\n The server is running " +
                sVersion
            ;
            return -1;
        }


    } catch (std::exception& e) {
        std::cerr<<e.what()<<std::endl;
        return -1;
    }
    return 0;

    while(true) {
        int pos_x, pos_y;
        player.getYX(pos_y, pos_x);

        //move camera to player
        this->camera.moveTo(pos_y, pos_x);
        this->camera.render(this->screen, this->world, this->player);
        this->screen.render();
        this->screen.clear();
        unsigned int input = getch();
        switch(input) {
            case KEY_UP:
                this->player.move(-1,0);
                break;
            case KEY_DOWN:
                this->player.move(1,0);
                break;
            case KEY_LEFT:
                this->player.move(0,-1);
                break;
            case KEY_RIGHT:
                this->player.move(0,1);
                break;
            case 27: //ESC
                return 0;
                break;
        };
    }
    return 0;
}

void Game::configure()
{
    ConfigLoader::load(); 

    WorldChunk::configure();
    World::configure();
    City::load_city_names();

    this->world = World(
        ConfigLoader::getStringOption(
            Game::configWorldNameKey,
            Game::defaultWorldName
        )
    );

    this->version = ConfigLoader::getVersion();

    std::cout<<"chunk_height: "<<ConfigLoader::getIntOption("chunk_height")<<'\n';
    std::cout<<"chunk_width: "<<ConfigLoader::getIntOption("chunk_width")<<'\n';
    std::cout<<"max_cities_per_chunk: "<<ConfigLoader::getIntOption("max_cities_per_chunk")<<'\n';
    std::cout<<std::endl;

    unsigned int chunkHeight = ConfigLoader::getIntOption("chunk_height");
    unsigned int chunkWidth  = ConfigLoader::getIntOption("chunk_width");
    
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    this->screenHeight = maxY;
    this->screenWidth = maxX;

    WorldChunk::setMaxYX(maxY, maxX);
}

std::string Game::checkVersion()
{
    std::string message = boost::lexical_cast<std::string>(Server::VERSION_CHECK) + " " + this->version + "\n";
    std::cerr<<message;
    this->connection.write(message);
    std::string response = this->connection.read();
    std::stringstream ss;

    ss.str(response);
    int responseType;
    ss>>responseType;
    if (responseType == Server::VERSION_CHECK_OK) {
        return "";
    } else if (responseType == Server::VERSION_INCOMPATIBLE) {
        std::string serverVersion;
        ss>>serverVersion;
        return serverVersion;
    }
}

int Game::login()
{
    std::string message = boost::lexical_cast<std::string>(Server::LOGIN) + " Username Password\n";
    std::cerr<<message;
    this->connection.write(message);
}
