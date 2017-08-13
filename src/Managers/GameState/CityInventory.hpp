#ifndef CITY_INVENTORY_HPP
#define CITY_INVENTORY_HPP

#include <string>
#include <vector>

#include "Managers/GameState/State.hpp"
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
            CCountQuestion,
            PCountQuestion,
            DisplayResults
        };

        State state;
        City city;
        int playerIndex;
        Player player;

        int playerItemSelected;
        int playerCountSelected;
        int cityItemSelected;
        int cityCountSelected;

        std::vector<std::string> cityInventoryOptions;
        std::vector<std::string> playerInventoryOptions;

        std::vector<std::string> getInventory(std::vector<Inventory::Record> inv);
        void populateMenu(Component::Menu *menu, std::vector<std::string> options);

        void updateCityInventory(WorldInteractionInterface ** worldProxy, Context *ctx);
        void updatePlayerInventory(WorldInteractionInterface ** worldProxy, Context *ctx);
        void updateCCountQuestion(WorldInteractionInterface ** worldProxy, Context *ctx);
        void updatePCountQuestion(WorldInteractionInterface ** worldProxy, Context *ctx);
        void updateDisplayResults(WorldInteractionInterface ** worldProxy, Context *ctx);

        void renderCityInventory(WorldInteractionInterface * worldProxy, Window::window_ptr window);
        void renderPlayerInventory(WorldInteractionInterface * worldProxy, Window::window_ptr window);
        void renderCCountQuestion(WorldInteractionInterface * worldProxy, Window::window_ptr window);
        void renderPCountQuestion(WorldInteractionInterface * worldProxy, Window::window_ptr window);
        void renderDisplayResults(WorldInteractionInterface * worldProxy, Window::window_ptr window);

        void popState();
        void pushState(State newState);

        bool inventoryShouldClose;
        Component::Menu cityInv;
        Component::Menu playerInv;
        Component::TextInput countInput;
    };
}

#endif //CITY_INVENTORY_HPP
