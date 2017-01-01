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
        int pos_x, pos_y;
        player.getYX(pos_y, pos_x);

        this->camera.moveTo(
            -pos_y + (this->screenHeight / 2), 
            -pos_x + (this->screenWidth / 2)
        );
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
}

void Game::configure()
{
    ConfigLoader::load(); 

    WorldChunk::configure();
    World::configure();
    City::load_city_names();

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
