#include "Managers/GameState/ServerHistory.hpp"

const std::string GameState::ServerHistory::historyPath = "GameData/server_history.txt";
const int GameState::ServerHistory::historyLength = 15;

GameState::ServerHistory::ServerHistory()
{

}

GameState::ServerHistory::~ServerHistory()
{

}

void GameState::ServerHistory::init()
{
    this->myState = InMenu;
    this->history = std::vector<std::string>();
    this->connectionOptions= std::vector<std::string>();
    this->connectionOptions.push_back("Connect");
    this->connectionOptions.push_back("Delete");
    this->connectionOptions.push_back("Back");
    this->history.push_back("New");
    this->close = false;
    this->newState = NULL;
    this->loadHistory();
    this->menu = Component::Menu("Which connection?", this->history, 0, 0, 20, 20);
    this->connectionMenu = Component::Menu("What do?", this->connectionOptions, 0, 0, 20, 20);
}

void GameState::ServerHistory::update(WorldInteractionInterface ** worldProxy, Context *ctx) 
{
    switch (this->myState) {
        case InMenu:
            this->updateMenu(worldProxy, ctx);
            break;
        case AddingHost:
            this->updateNewHost(worldProxy, ctx);
            break;
        case ConnectionMenu:
            this->updateConnectionMenu(worldProxy, ctx);
    };
}

void GameState::ServerHistory::render(WorldInteractionInterface * worldProxy, Window::window_ptr window)
{
    switch (this->myState) {
        case InMenu:
            this->renderMenu(worldProxy, window);
            break;
        case AddingHost:
            this->renderNewHost(worldProxy, window);
            break;
        case ConnectionMenu:
            this->renderConnectionMenu(worldProxy, window);
    };
}

GameState::State *GameState::ServerHistory::nextState()
{
    return this->newState;
}

void GameState::ServerHistory::clearNextState()
{
    this->newState = NULL;
}

bool GameState::ServerHistory::shouldClose()
{
    return this->close;
}

void GameState::ServerHistory::renderMenu(WorldInteractionInterface * worldProxy, Window::window_ptr window)
{
    int borderHeight = window->getHeight() * 0.1;
    int borderWidth = window->getWidth() * 0.1;
    this->menu.setDims(
        borderHeight, 
        borderWidth,
        window->getHeight() - (2 * borderHeight),
        window->getWidth() - (2 * borderWidth)
    );
    this->menu.render(window);
}

void GameState::ServerHistory::renderNewHost(WorldInteractionInterface * worldProxy, Window::window_ptr window)
{
    this->newHost.render(window);
}

void GameState::ServerHistory::renderConnectionMenu(WorldInteractionInterface * worldProxy, Window::window_ptr window)
{
    int borderHeight = window->getHeight() * 0.1;
    int borderWidth = window->getWidth() * 0.1;
    this->connectionMenu.setDims(
        borderHeight, 
        borderWidth,
        window->getHeight() - (2 * borderHeight),
        window->getWidth() - (2 * borderWidth)
    );
    this->connectionMenu.render(window);
}

void GameState::ServerHistory::updateMenu(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    switch (ctx->input) {
        case Input::ESCAPE:
            this->msgDown = -1;
            this->close = true;
            return;
    }

    int result = this->menu.update(ctx);
    switch (result) {
        case -1:
            break;
        case -2:
            this->logger->debug("Back pressed");
            this->msgDown = -1;
            this->close = true;
            break;
        case 0:
            this->myState = AddingHost;
            this->newHost = Component::TextInput("New Host (hostname:port): ", 5, 5);
            break;
        default:
            this->selectedHistory = result;
            this->myState = ConnectionMenu;
            this->connectionMenu = Component::Menu(this->history[result], this->connectionOptions, 0, 0, 20, 20);
            break;
    };
}


void GameState::ServerHistory::updateNewHost(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    std::string newHost = this->newHost.update(ctx);
    if (this->newHost.done()) {
        this->history.push_back(newHost);
        this->saveHistory();
        this->menu = Component::Menu("Which connection?", this->history, 0, 0, 20, 20);
        this->myState = InMenu;
    }
}

void GameState::ServerHistory::updateConnectionMenu(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    switch(ctx->input) {
        case Input::ESCAPE:
            this->myState = InMenu;
            return;
    }

    int result = this->connectionMenu.update(ctx);
    switch (result) {
        case -1:
            break;
        case -2:
            this->myState = InMenu;
            break;
        case 0:
            if ((*worldProxy) != NULL) {
                delete (*worldProxy);
            }
            (*worldProxy) = new NetworkedWorldInteraction(
                this->hostname(this->history[this->selectedHistory]),
                this->port(this->history[this->selectedHistory])
            );
            if (!(*worldProxy)->loadWorld(this->logger)) {
                this->logger->warn("Could not connect to server");
                this->myState = InMenu;
                return;
            }
            this->newState = new GameState::Playing;
            this->logger->debug("%d Selected", result);
            break;
        case 1:
            this->removeHistory(this->selectedHistory);
            this->saveHistory();
            this->menu = Component::Menu("Which connection?", this->history, 0, 0, 20, 20);
            this->myState = InMenu;
            break;
        case 2:
            this->myState = InMenu;
            break;
    };
}

void GameState::ServerHistory::loadHistory()
{
    std::ifstream ifile;
    ifile.open(GameState::ServerHistory::historyPath.c_str());
    while (ifile.good()) {
        std::string tmp;
        ifile>>tmp;
        if (tmp != "") {
            this->history.push_back(tmp);
        }
    }
    ifile.close();
}

void GameState::ServerHistory::saveHistory()
{
    std::ofstream ofile;
    ofile.open(GameState::ServerHistory::historyPath.c_str());
    int maxHistory = std::min(
        int(this->history.size()), 
        GameState::ServerHistory::historyLength
    );
    for (int i = 1; i < maxHistory; ++i) {
        ofile<<this->history[i]<<std::endl;
    }
    ofile.close();
}

void GameState::ServerHistory::removeHistory(int index)
{
    for (int i = index + 1; i < this->history.size(); ++i) {
        this->history[i-1] = this->history[i];
    }
    this->history.pop_back();
}

std::string GameState::ServerHistory::hostname(std::string host)
{
    return host.substr(0, host.find(":"));
}

std::string GameState::ServerHistory::port(std::string host)
{
    return host.substr(host.find(":") + 1);
}

