#include "Managers/Game.hpp"

const std::string Game::configWorldNameKey = "world_name";
const std::string Game::defaultWorldName = "world";

Game::Game()
{
    this->worldProxy = NULL;
}

Game::~Game()
{
    if (this->worldProxy != NULL) {
        delete this->worldProxy;
    }
}

int Game::setup()
{
    this->configure();

    this->camera = Camera(0, 0);
    this->screen = Screen();
    this->screen.init();

    this->player = Player("Bob", 0, 0);

    this->worldProxy->loadWorld();

    return 0;
}

int Game::run()
{
    refresh();

    int height, width;
    getmaxyx(stdscr, height, width);
    Window consoleWin = Window(
        this->screen.getHeight() + 3,
        0,
        height - (this->screen.getHeight() + 3),
        0 
    );
    consoleWin.putstr(1, 1, "Hello, World");

    while(true) {
        int pos_x, pos_y;
        player.getYX(pos_y, pos_x);

        //move camera to player
        this->camera.moveTo(pos_y, pos_x);
        this->worldProxy->movePlayerToCoordinate(pos_y, pos_x);
        this->camera.render(this->screen, *this->worldProxy, this->player);
        this->screen.render();
        consoleWin.render();
        this->screen.clear();
        unsigned int input = this->screen.getCh();
        switch(input) {
            case 119:
                this->player.move(-1,0);
                break;
            case 115:
                this->player.move(1,0);
                break;
            case 97:
                this->player.move(0,-1);
                break;
            case 100:
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

    //this->worldProxy = new LocalWorldInteraction(
    //    ConfigLoader::getStringOption(
    //        Game::configWorldNameKey,
    //        Game::defaultWorldName
    //    )
    //);
    
    this->worldProxy = new NetworkedWorldInteraction(
        "localhost",
        "9797"
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

