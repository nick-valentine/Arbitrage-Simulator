#include "Managers/Game.hpp"

const std::string Game::configWorldNameKey = "world_name";
const std::string Game::defaultWorldName = "world";

Keymap Game::keymap = Keymap();

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

    this->gameWindow = Window::window_ptr(new GameWindow());
    this->gameWindow->init();

    this->consoleWindow = Window::window_ptr(new ConsoleWindow());
    this->consoleWindow->init();

    this->windowLayout.addWindow("GameWindow", this->gameWindow);
    this->windowLayout.setMainWindow("GameWindow");

    this->windowLayout.addWindow("ConsoleWindow", this->consoleWindow);
    this->windowLayout.setSubWindow("ConsoleWindow");
    this->windowLayout.setSubWindowMinHeight(20);
    this->windowLayout.render();

    this->logger = boost::shared_ptr<Logger>(
        boost::dynamic_pointer_cast<ConsoleWindow>(this->consoleWindow)->getLogger()
    );

    Game::keymap.init();

    this->worldProxy->loadWorld(this->logger);

    this->stateStack.push(new GameState::Playing());
    this->stateStack.top()->init();
    this->stateStack.top()->setLogger(this->logger);

    return 0;
}

int Game::run()
{
    refresh();
    this->logger->info("Game Starting");

    Input input = Input::IGNORED;

    while(true) {
        this->logger->info("Game Ticking");

        this->stateStack.top()->render(
            this->worldProxy,
            this->gameWindow
        );

        this->windowLayout.render();
        this->gameWindow->clear();

        int rawInput = this->gameWindow->getCh();
        logger->debug("%d Pressed", rawInput);
        input = Game::keymap.convert(rawInput);
        logger->debug("%d Pressed", input);

        if (input == Input::ESCAPE) {
            return 0;
        }

        this->stateStack.top()->update(
            this->worldProxy,
            input
        );

        if (this->stateStack.top()->shouldClose()) {
            this->logger->info("saving reference to old state");
            GameState::State * oldState = this->stateStack.top();
            this->logger->info("popping state off stack");
            this->stateStack.pop();
            if (this->stateStack.size() == 0) {
                this->logger->info("closing down program");
                return 0;
            }
            this->logger->info("transferring message");
            this->stateStack.top()->recvUp(oldState->passDown());
            this->logger->info("deleting old state");
            delete oldState;
        } else if (this->stateStack.top()->nextState() != NULL) {
            this->logger->info("New state being set");
            GameState::State *oldState = this->stateStack.top();
            oldState->nextState()->recvDown(
                this->stateStack.top()->passUp()
            );
            oldState->nextState()->setLogger(this->logger);
            this->logger->info("Pushing the new state");
            this->stateStack.push(
                oldState->nextState()
            );
            oldState->clearNextState();
        }
    }
    return 0;
}

void Game::configure()
{
    ConfigLoader::load(); 

    Logger::configure();
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

