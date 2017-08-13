#ifndef CITY_INVENTORY_HPP
#define CITY_INVENTORY_HPP

#include <string>
#include <vector>

#include "Managers/GameState/State.hpp"
#include "GameObjects/City.hpp"
#include "Components/Menu.hpp"

namespace GameState
{
    class CityInventory : public State
    {
    public:
        CityInventory();
        ~CityInventory();
        void init();
        void setCity(City city);
        void setPlayer(int index, Player player);
        void update(WorldInteractionInterface ** worldProxy, Context *ctx);
        void render(WorldInteractionInterface *worldProxy, Window::window_ptr window);
        State *nextState();
        void clearNextState();
        bool shouldClose();
    private:
        enum State {
            CInventory = 0,
            PInventory
        };

        State state;
        City city;
        int playerIndex;
        Player player;
        std::vector<std::string> cityInventoryOptions;
        std::vector<std::string> playerInventoryOptions;

        std::vector<std::string> getInventory(std::vector<Inventory::Record> inv);
        void populateMenu(Component::Menu *menu, std::vector<std::string> options);

        void updateCityInventory(WorldInteractionInterface ** worldProxy, Context *ctx);
        void updatePlayerInventory(WorldInteractionInterface ** worldProxy, Context *ctx);

        bool inventoryShouldClose;
        Component::Menu cityInv;
        Component::Menu playerInv;
    };
}

#endif //CITY_INVENTORY_HPP
