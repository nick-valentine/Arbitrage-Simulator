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
    this->history = std::vector<std::string>();
    this->history.push_back("New");
    this->close = false;
    this->newState = NULL;
    this->loadHistory();
    this->menu = Component::Menu("Which connection?", this->history, 0, 0, 20, 20);
}

void GameState::ServerHistory::update(WorldInteractionInterface ** worldProxy, Context *ctx)
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
            // push a new input new server state
        default:
            if ((*worldProxy) != NULL) {
                delete (*worldProxy);
            }
            (*worldProxy) = new NetworkedWorldInteraction(
                this->hostname(this->history[result]),
                this->port(this->history[result])
            );
            (*worldProxy)->loadWorld(this->logger);
            this->newState = new GameState::Playing;
            this->logger->debug("%d Selected", result);
            break;
    };
}

void GameState::ServerHistory::render(WorldInteractionInterface * worldProxy, Window::window_ptr window)
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

void GameState::ServerHistory::loadHistory()
{
    std::ifstream ifile;
    ifile.open(GameState::ServerHistory::historyPath.c_str());
    while (ifile.good()) {
        std::string tmp;
        ifile>>tmp;
        this->history.push_back(tmp);
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

std::string GameState::ServerHistory::hostname(std::string host)
{
    return host.substr(0, host.find(":"));
}

std::string GameState::ServerHistory::port(std::string host)
{
    return host.substr(host.find(":") + 1);
}

