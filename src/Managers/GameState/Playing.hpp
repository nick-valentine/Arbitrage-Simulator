#ifndef GAMESTATE_PLAYING_HPP
#define GAMESTATE_PLAYING_HPP

#include "Camera.hpp"
#include "GameObjects/Player.hpp"
#include "Managers/GameState/State.hpp"

class Playing : public State
{
public:
    void init();
    void update(WorldInteractionInterface *worldProxy, Input input);
    void render(WorldInteractionInterface *worldProxy, Window::window_ptr window);
    State *nextState();
    bool shouldClose();
private:
    Player player;
    Camera camera;
};

#endif //GAMESTATE_PLAYING_HPP
