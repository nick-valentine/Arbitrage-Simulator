#include "Managers/GameState/MainMenu.hpp"

GameState::MainMenu::MainMenu()
{

}

GameState::MainMenu::~MainMenu()
{

}

void GameState::MainMenu::init()
{
    this->logger = Logger::LoggerPtr(new NullLogger());
    std::vector<std::string> options;
    options.push_back("Play Game");
    options.push_back("Connect To Server");
    options.push_back("Quit");
    this->menu= Component::Menu("What do?", options, 10, 10, 20, 20);
    this->close = false;
    this->newState = NULL;
    Tile::setPallete();
}

void GameState::MainMenu::update(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    int result = this->menu.update(ctx);
    switch (result) {
        case -1:
            break;
        case -2:
            this->logger->debug("Back pressed");
            this->msgDown = -1;
            this->close = true;
            break;
        case 0:
            if ((*worldProxy) != NULL) {
                delete (*worldProxy);
            }
            (*worldProxy) = new LocalWorldInteraction(
                ConfigLoader::getStringOption(
                    Game::configWorldNameKey,
                    Game::defaultWorldName
                )
            );
            (*worldProxy)->loadWorld(this->logger);
            this->newState = new GameState::Playing;
            break;
        case 1:
            if ((*worldProxy) != NULL) {
                delete (*worldProxy);
            }
            (*worldProxy) = new NetworkedWorldInteraction(
                "localhost",
                "9797"
            );
            (*worldProxy)->loadWorld(this->logger);
            this->newState = new GameState::Playing;
            break;
        case 2:
            this->close = true;
            break;
        default:
            this->logger->debug("%d Selected", result);
            break;
    };
}

void GameState::MainMenu::render(WorldInteractionInterface *worldProxy, Window::window_ptr window)
{
    int borderHeight = window->getHeight() * 0.1;
    int borderWidth = window->getWidth() * 0.1;
    this->menu.setDims(
        borderHeight, 
        borderWidth,
        window->getHeight() - (2 * borderHeight),
        window->getWidth() - (2 * borderWidth)
    );
    this->menu.render(window);
}

GameState::State *GameState::MainMenu::nextState()
{
    return this->newState;
}

void GameState::MainMenu::clearNextState()
{
    this->newState = NULL;
}

bool GameState::MainMenu::shouldClose()
{
    return this->close;
}
