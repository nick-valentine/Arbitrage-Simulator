#ifndef GAMESTATE_SERVERHISTORY_HPP
#define GAMESTATE_SERVERHISTORY_HPP

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Components/Menu.hpp"
#include "Components/TextInput.hpp"
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

        enum HistoryState {
            InMenu,
            AddingHost,
            ConnectionMenu
        };

        void renderMenu(WorldInteractionInterface * worldProxy, Window::window_ptr window);
        void renderNewHost(WorldInteractionInterface * worldProxy, Window::window_ptr window);
        void renderConnectionMenu(WorldInteractionInterface * worldProxy, Window::window_ptr window);

        void updateMenu(WorldInteractionInterface ** worldProxy, Context *ctx);
        void updateNewHost(WorldInteractionInterface ** worldProxy, Context *ctx);
        void updateConnectionMenu(WorldInteractionInterface ** worldProxy, Context *ctx);

        void loadHistory();
        void saveHistory();
        void removeHistory(int index);

        std::string hostname(std::string host);
        std::string port(std::string host);

        std::vector<std::string> history;
        std::vector<std::string> connectionOptions;
        
        HistoryState myState;

        bool close;
        int selectedHistory;
        GameState::State *newState;
        Component::Menu menu;
        Component::Menu connectionMenu;
        Component::TextInput newHost;
    };
}

#endif //GAMESTATE_SERVERHISTORY_HPP
