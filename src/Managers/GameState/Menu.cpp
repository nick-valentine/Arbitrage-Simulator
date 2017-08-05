#include "Managers/GameState/Menu.hpp"

GameState::Menu::Menu()
{
    this->logger = Logger::LoggerPtr(new NullLogger());
    this->options = std::vector<std::string>();
    this->menuShouldClose = false;
    this->menu = Component::Menu();
}

GameState::Menu::~Menu()
{

}

void GameState::Menu::init()
{
    this->menu = Component::Menu(this->head, this->options, 10, 10, 30, 100);
    this->menuShouldClose = false;
}

void GameState::Menu::setHead(std::string head)
{
    this->head = head;
}

void GameState::Menu::addOption(std::string option)
{
    this->options.push_back(option);
}

void GameState::Menu::update(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    int result = this->menu.update(ctx);
    switch (result) {
        case -1:
            break;
        case -2:
            this->logger->debug("Back pressed");
            this->msgDown = -1;
            this->menuShouldClose = true;
            break;
        default:
            this->logger->debug("%d Selected", result);
            this->msgDown = result;
            this->menuShouldClose = true;
            break;
    };
}

void GameState::Menu::render(WorldInteractionInterface *worldProxy, Window::window_ptr window)
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

GameState::State *GameState::Menu::nextState()
{
    return NULL;
}

void GameState::Menu::clearNextState()
{

}

bool GameState::Menu::shouldClose()
{
    return this->menuShouldClose;
}
