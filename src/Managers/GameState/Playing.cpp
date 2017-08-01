#include "Managers/GameState/Playing.hpp"

void GameState::Playing::init()
{
    this->player = Player("Bob", 200, 200);
    this->logger = Logger::LoggerPtr(new NullLogger());
    this->camera = Camera(0, 0);
}

void GameState::Playing::update(WorldInteractionInterface *worldProxy, Input input)
{
    switch(input) {
        case Input::UP:
            this->player.move(-1,0);
            break;
        case Input::DOWN:
            this->player.move(1,0);
            break;
        case Input::LEFT:
            this->player.move(0,-1);
            break;
        case Input::RIGHT:
            this->player.move(0,1);
            break;
        case Input::BACK:
            GameState::Menu *menuState = new GameState::Menu;
            menuState->addOption("yes");
            menuState->addOption("no");
            menuState->addOption("maybe");
            menuState->addOption("sometimes");
            menuState->init();
            this->newState = menuState;
            break;
    };
}

void GameState::Playing::render(WorldInteractionInterface *worldProxy, Window::window_ptr window)
{
    int pos_x, pos_y;
    player.getYX(pos_y, pos_x);

    //move camera to player
    this->camera.moveTo(pos_y, pos_x);
    worldProxy->movePlayerToCoordinate(pos_y, pos_x);
    this->camera.render(
        window, 
        *worldProxy, 
        this->player
    );
}

GameState::State *GameState::Playing::nextState()
{
    return this->newState;
}

void GameState::Playing::clearNextState()
{
    this->newState = NULL;
}

bool GameState::Playing::shouldClose()
{
    return false;
}
