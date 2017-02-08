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
    using boost::asio::ip::tcp;
    try {
        std::string server = "localhost";
        std::string serviceName = "9797";
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(server.c_str(), serviceName.c_str());
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        boost::system::error_code ignored_error;
        std::string message = boost::lexical_cast<std::string>(Server::LOGIN) + " Username Password\n";
        std::cerr<<message;
        boost::asio::write(socket, boost::asio::buffer(message), ignored_error);

        while(true) {
            boost::array<char, 128> buff;
            boost::system::error_code error;

            std::size_t len = socket.read_some(boost::asio::buffer(buff), error);
    
            if (error == boost::asio::error::eof) {
                break; //connection closed
            } else if (error) {
                throw boost::system::system_error(error);
            }
            std::cerr.write(buff.data(), len);
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
