#ifndef GAMESTATE_PLAYING_HPP
#define GAMESTATE_PLAYING_HPP

#include <sstream>
#include <string>

#include "Camera.hpp"
#include "GameObjects/City.hpp"
#include "GameObjects/Inventory.hpp"
#include "GameObjects/ItemMap.hpp"
#include "GameObjects/Player.hpp"
#include "GameObjects/Tile.hpp"
#include "Managers/GameState/Menu.hpp"
#include "Managers/GameState/State.hpp"

namespace GameState
{
    class Playing : public State
    {
    public:
        void init();
        void update(WorldInteractionInterface *worldProxy, Input input);
        void render(WorldInteractionInterface *worldProxy, Window::window_ptr window);
        State *nextState();
        void clearNextState();
        bool shouldClose();
    private:
        void getCityInventory(City *city);
        void populateMenu(GameState::Menu *menu, std::vector<std::string> options);

        std::vector<Inventory::Record> cityInventory;
        std::vector<std::string> cityInventoryOptions;

        Player player;
        Camera camera;
        GameState::State *newState;
    };
}

#endif //GAMESTATE_PLAYING_HPP
