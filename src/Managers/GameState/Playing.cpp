#include "Managers/GameState/Playing.hpp"

void GameState::Playing::init()
{
    this->player = Player("Bob", 200, 200);
    this->logger = Logger::LoggerPtr(new NullLogger());
    this->camera = Camera(0, 0);
    this->close  = false;
    this->newState = NULL;
}

void GameState::Playing::update(WorldInteractionInterface ** worldProxy, Context *ctx)
{

    if (this->recvMsgUp != 0) {
        this->logger->info("Recieved message %i", this->recvMsgUp);
    }

    switch(ctx->input) {
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
        case Input::ESCAPE:
            this->close = true;
            break;
    };
    int pos_y, pos_x;
    this->player.getYX(pos_y, pos_x);
    (*worldProxy)->movePlayerToCoordinate(pos_y, pos_x);
    Tile tile = (*worldProxy)->getTileUnderPlayer();
    this->logger->info("Player stepped on tile at height: %i", tile.getElevation());
    this->logger->info("Player is on tile: %i, %i", pos_x, pos_y);
    if (tile.getType() == Tile::CITIES) {
        City city = (*worldProxy)->getCity(pos_y, pos_x);
        GameState::CityInventory *cityInventoryScreen = new GameState::CityInventory;
        cityInventoryScreen->setCity(city);
        this->newState = cityInventoryScreen;
        this->logger->info("This tile is a city: %s", city.getName().c_str());
    }
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
    return this->close;
}

