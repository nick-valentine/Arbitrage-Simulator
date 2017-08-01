#ifndef GAMESTATE_PLAYING_HPP
#define GAMESTATE_PLAYING_HPP

#include "Camera.hpp"
#include "GameObjects/Player.hpp"
#include "Managers/GameState/State.hpp"
#include "Managers/GameState/Menu.hpp"

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
        Player player;
        Camera camera;
        GameState::State *newState;
    };
}

#endif //GAMESTATE_PLAYING_HPP
