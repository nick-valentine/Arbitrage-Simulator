#ifndef CITY_INVENTORY_HPP
#define CITY_INVENTORY_HPP

#include <string>
#include <vector>

#include "Managers/GameState/State.hpp"
#include "Services/Economy/CityTrade.hpp"
#include "GameObjects/City.hpp"
#include "GameObjects/ItemMap.hpp"
#include "Components/Menu.hpp"
#include "Components/TextInput.hpp"

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
            PInventory,
            CountQuestion,
            DisplayResults
        };

        enum Stage {
            p = 0,
            c
        };

        State state;
        State lastState;
        City city;
        int playerIndex;
        Player player;

        Stage stageFor;
        int itemStage;
        int countStage;

        Inventory playerStage;
        Inventory cityStage;

        std::vector<std::string> cityInventoryOptions;
        std::vector<std::string> playerInventoryOptions;

        std::vector<std::string> getInventory(std::vector<Inventory::Record> inv);
        void populateMenu(Component::Menu *menu, std::vector<std::string> options);

        void updateCityInventory(WorldInteractionInterface ** worldProxy, Context *ctx);
        void updatePlayerInventory(WorldInteractionInterface ** worldProxy, Context *ctx);
        void updateCountQuestion(WorldInteractionInterface ** worldProxy, Context *ctx);
        void updateDisplayResults(WorldInteractionInterface ** worldProxy, Context *ctx);

        void renderCityInventory(WorldInteractionInterface * worldProxy, Window::window_ptr window);
        void renderPlayerInventory(WorldInteractionInterface * worldProxy, Window::window_ptr window);
        void renderCountQuestion(WorldInteractionInterface * worldProxy, Window::window_ptr window);
        void renderDisplayResults(WorldInteractionInterface * worldProxy, Window::window_ptr window);

        void popState();
        void pushState(State newState);

        void displayItem(Window::window_ptr window, Inventory::Record rec, int y, int x);

        bool inventoryShouldClose;
        Component::Menu cityInv;
        Component::Menu playerInv;
        Component::TextInput countInput;
    };
}

#endif //CITY_INVENTORY_HPP
