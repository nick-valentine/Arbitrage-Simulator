#ifndef GAMESTATE_MENU_HPP
#define GAMESTATE_MENU_HPP

#include <string>
#include <vector>

#include "Managers/GameState/State.hpp"
#include "Components/Menu.hpp"

namespace GameState
{
    class Menu : public State
    {
    public:
        Menu();
        ~Menu();
        void init();
        void addOption(std::string option);
        void update(WorldInteractionInterface *worldProxy, Input input);
        void render(WorldInteractionInterface *worldProxy, Window::window_ptr window);
        State *nextState();
        void clearNextState();
        bool shouldClose();
    private:
        std::vector<std::string> options;
        bool menuShouldClose;
        Component::Menu menu;
    };
}

#endif //GAMESTATE_MENU_HPP
