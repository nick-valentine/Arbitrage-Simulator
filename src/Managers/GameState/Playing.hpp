#ifndef GAMESTATE_PLAYING_HPP
#define GAMESTATE_PLAYING_HPP

#include <sstream>
#include <string>

#include "Camera.hpp"
#include "GameObjects/City.hpp"
#include "GameObjects/Inventory.hpp"
#include "GameObjects/ItemMap.hpp"
#include "GameObjects/Tile.hpp"
#include "Managers/GameState/Menu.hpp"
#include "Managers/GameState/CityInventory.hpp"
#include "Managers/GameState/State.hpp"

namespace GameState
{
    class Playing : public State
    {
    public:
        void init();
        void update(WorldInteractionInterface ** worldProxy, Context *ctx);
        void render(WorldInteractionInterface *worldProxy, Window::window_ptr window);
        State *nextState();
        void clearNextState();
        bool shouldClose();
    private:
        bool close;
        int player;
        Camera camera;
        GameState::State *newState;
        Tile lastTile;
    };
}

#endif //GAMESTATE_PLAYING_HPP
