#ifndef GAMESTATE_MAIN_MENU
#define GAMESTATE_MAIN_MENU

#include "Components/Menu.hpp"
#include "GameObjects/Tile.hpp"
#include "Managers/Game.hpp"
#include "Managers/GameState/Playing.hpp"
#include "Managers/GameState/State.hpp"

#include "Services/WorldInteraction/LocalWorldInteraction.hpp"
#include "Services/WorldInteraction/NetworkedWorldInteraction.hpp"

namespace GameState
{
    class MainMenu : public State
    {
    public:
        MainMenu();
        ~MainMenu();
        void init();
        void update(WorldInteractionInterface ** worldProxy, Context *ctx);
        void render(WorldInteractionInterface *worldProxy, Window::window_ptr window);
        State *nextState();
        void clearNextState();
        bool shouldClose();
    private:
        bool close;
        GameState::State *newState;

        Component::Menu menu;
    };
}

#endif //GAMESTATE_MAIN_MENU
