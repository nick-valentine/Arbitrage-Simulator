#include "Managers/GameState/Playing.hpp"

void GameState::Playing::init()
{
    this->player = -1;
    this->logger = Logger::LoggerPtr(new NullLogger());
    this->camera = Camera(0, 0);
    this->close  = false;
    this->newState = NULL;
}

void GameState::Playing::update(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    if (this->player == -1) {
        std::string name;
        srand( time( NULL) );
        for (int i = 0; i < 5; ++i) {
            name += char((rand() % 26) + 97);
        }
        this->player = (*worldProxy)->getPlayer(name);
    }

    if (this->recvMsgUp != 0) {
        this->logger->info("Recieved message %i", this->recvMsgUp);
        this->recvMsgUp = 0;
    }

    switch(ctx->input) {
        case Input::UP:
            (*worldProxy)->movePlayer(this->player, -1, 0);
            break;
        case Input::DOWN:
            (*worldProxy)->movePlayer(this->player, 1, 0);
            break;
        case Input::LEFT:
            (*worldProxy)->movePlayer(this->player, 0, -1);
            break;
        case Input::RIGHT:
            (*worldProxy)->movePlayer(this->player, 0, 1);
            break;
        case Input::ESCAPE:
            (*worldProxy)->cleanup();
            delete (*worldProxy);
            (*worldProxy) = NULL;
            this->close = true;
            return;
    };
    Tile tile = (*worldProxy)->getTileUnderPlayer(this->player);
    int pos_y, pos_x;
    (*worldProxy)->playerInfo(this->player).getYX(pos_y, pos_x);
    if (tile.getType() == Tile::CITIES && lastTile.getType() != Tile::CITIES) {
        City city = (*worldProxy)->getCity(pos_y, pos_x);
        GameState::CityInventory *cityInventoryScreen = new GameState::CityInventory;
        cityInventoryScreen->setCity(city);
        cityInventoryScreen->setPlayer(this->player, (*worldProxy)->playerInfo(this->player));
        this->newState = cityInventoryScreen;
    }

    this->lastTile = tile;
}

void GameState::Playing::render(WorldInteractionInterface *worldProxy, Window::window_ptr window)
{
    int pos_x, pos_y;
    worldProxy->playerInfo(this->player).getYX(pos_y, pos_x);

    //move camera to player
    this->camera.moveTo(pos_y, pos_x);
    this->camera.render(
        window, 
        *worldProxy
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
    return this->close;
}

