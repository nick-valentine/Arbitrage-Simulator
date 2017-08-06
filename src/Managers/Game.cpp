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

    this->stateStack.push(new GameState::MainMenu());
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
        this->stateStack.top()->render(
            this->worldProxy,
            this->gameWindow
        );

        this->windowLayout.render();
        this->gameWindow->clear();

        int rawInput = this->gameWindow->getCh();
        input = Game::keymap.convert(rawInput);

        Context ctx;
        ctx.input = input;
        ctx.rawInput = rawInput;

        this->stateStack.top()->update(
            &this->worldProxy,
            &ctx
        );

        if (this->stateStack.top()->shouldClose()) {
            GameState::State * oldState = this->stateStack.top();
            this->stateStack.pop();
            if (this->stateStack.size() == 0) {
                return 0;
            }
            this->stateStack.top()->recvUp(oldState->passDown());
            delete oldState;
        } else if (this->stateStack.top()->nextState() != NULL) {
            GameState::State *newState = this->stateStack.top()->nextState();
            GameState::State *oldState = this->stateStack.top();
            newState->init();
            newState->recvDown(oldState->passUp());
            newState->setLogger(this->logger);
            this->stateStack.push(newState);
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

    unsigned int chunkHeight = ConfigLoader::getIntOption("chunk_height");
    unsigned int chunkWidth  = ConfigLoader::getIntOption("chunk_width");
    
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    this->screenHeight = maxY;
    this->screenWidth = maxX;

    WorldChunk::setMaxYX(maxY, maxX);
}

