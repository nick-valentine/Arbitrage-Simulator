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
        void update(WorldInteractionInterface *worldProxy, Context *ctx);
        void render(WorldInteractionInterface *worldProxy, Window::window_ptr window);
        State *nextState();
        void clearNextState();
        bool shouldClose();
    private:
        City city;
        std::vector<std::string> options;
        std::vector<Inventory::Record> cityInventory;
        std::vector<std::string> cityInventoryOptions;

        void getCityInventory(City *city);
        void populateMenu(Component::Menu *menu, std::vector<std::string> options);

        bool inventoryShouldClose;
        Component::Menu inventory;
    };
}

#endif //CITY_INVENTORY_HPP
