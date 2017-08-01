#include "Managers/GameState/Menu.hpp"

GameState::Menu::Menu()
{
    this->logger = Logger::LoggerPtr(new NullLogger());
}

GameState::Menu::~Menu()
{

}

void GameState::Menu::init()
{
    this->menu = Component::Menu(this->options, 10, 10, 30, 100);
    this->menuShouldClose = false;
}

void GameState::Menu::addOption(std::string option)
{
    this->options.push_back(option);
}

void GameState::Menu::update(WorldInteractionInterface *worldProxy, Input input)
{
    int result = this->menu.update(input);
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
