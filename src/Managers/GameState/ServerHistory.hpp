#ifndef GAMESTATE_SERVERHISTORY_HPP
#define GAMESTATE_SERVERHISTORY_HPP

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Components/Menu.hpp"
#include "Managers/GameState/State.hpp"
#include "Managers/GameState/Playing.hpp"

#include "Services/WorldInteraction/NetworkedWorldInteraction.hpp"

namespace GameState
{
    class ServerHistory : public State
    {
    public:
        ServerHistory();
        ~ServerHistory();
        void init();
        void update(WorldInteractionInterface ** worldProxy, Context *ctx);
        void render(WorldInteractionInterface * worldProxy, Window::window_ptr window);
        State *nextState();
        void clearNextState();
        bool shouldClose();
    private:
        const static std::string historyPath;
        const static int historyLength;

        void loadHistory();
        void saveHistory();

        std::string hostname(std::string host);
        std::string port(std::string host);

        std::vector<std::string> history;

        bool close;
        GameState::State *newState;
        Component::Menu menu;
    };
}

#endif //GAMESTATE_SERVERHISTORY_HPP
