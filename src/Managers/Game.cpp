#include "Managers/Game.hpp"

const std::string Game::configWorldNameKey = "world_name";
const std::string Game::defaultWorldName = "world";

Game::Game()
{

}

int Game::setup()
{
    this->pos_x = 0;
    this->pos_y = 0;

    this->configure();

    this->camera = Camera(0, 0);
    this->screen = Screen();

    this->world = World(
        ConfigLoader::getStringOption(
            Game::configWorldNameKey,
            Game::defaultWorldName
        )
    );
    this->world.generateWorld();
}

int Game::run()
{
    while(true) {
        this->camera.moveTo(this->pos_y, this->pos_x);
        this->camera.render(this->screen, this->world);
        this->screen.render();
        this->screen.clear();
        unsigned int input = getch();
        switch(input) {
            case KEY_UP:
                pos_y++;
                break;
            case KEY_DOWN:
                pos_y--;
                break;
            case KEY_LEFT:
                pos_x++;
                break;
            case KEY_RIGHT:
                pos_x--;
                break;
            case 27: //ESC
                return 0;
                break;
        };
    }
}

void Game::configure()
{
    ConfigLoader::load(); 

    WorldChunk::configure();
    City::load_city_names();

    std::cout<<"chunk_height: "<<ConfigLoader::getIntOption("chunk_height")<<'\n';
    std::cout<<"chunk_width: "<<ConfigLoader::getIntOption("chunk_width")<<'\n';
    std::cout<<"max_cities_per_chunk: "<<ConfigLoader::getIntOption("max_cities_per_chunk")<<'\n';
    std::cout<<std::endl;

    unsigned int chunkHeight = ConfigLoader::getIntOption("chunk_height");
    unsigned int chunkWidth  = ConfigLoader::getIntOption("chunk_width");

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    WorldChunk::setMaxYX(maxY, maxX);
}
