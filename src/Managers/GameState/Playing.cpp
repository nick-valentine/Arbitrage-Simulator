#include "Managers/GameState/Playing.hpp"

void Playing::init()
{
    this->player = Player("Bob", 200, 200);
    this->logger = Logger::LoggerPtr(new NullLogger());
    this->camera = Camera(0, 0);
}

void Playing::update(WorldInteractionInterface *worldProxy, Input input)
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
//            this->state = MENU;
            break;
    };
}

void Playing::render(WorldInteractionInterface *worldProxy, Window::window_ptr window)
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

State *Playing::nextState()
{

}

bool Playing::shouldClose()
{

}
