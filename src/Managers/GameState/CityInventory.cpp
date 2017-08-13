#include "Managers/GameState/CityInventory.hpp"

GameState::CityInventory::CityInventory()
{
    this->logger = Logger::LoggerPtr(new NullLogger());
}

GameState::CityInventory::~CityInventory()
{

}

void GameState::CityInventory::init()
{
    this->cityInv = Component::Menu("", std::vector<std::string>(), 10, 10, 20, 20);
    this->playerInv = Component::Menu("", std::vector<std::string>(), 10, 10, 20, 20);
    this->inventoryShouldClose = false;
    this->cityInventoryOptions = this->getInventory(this->city.getInventory()->getInv());
    this->populateMenu(&this->cityInv, this->cityInventoryOptions);
    this->playerInventoryOptions = this->getInventory(this->player.getInventory()->getInv());
    this->populateMenu(&this->playerInv, this->playerInventoryOptions);
    this->countInput = Component::TextInput("How Many: ", 5, 5);
    this->state = CInventory;
}

void GameState::CityInventory::setCity(City city)
{
    this->city = city;
}

void GameState::CityInventory::setPlayer(int index, Player player)
{
    this->player = player;
    this->playerIndex = index;
}

void GameState::CityInventory::update(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    switch (this->state) {
        case CInventory:
            return this->updateCityInventory(worldProxy, ctx);
        case PInventory:
            return this->updatePlayerInventory(worldProxy, ctx);
        case CCountQuestion:
            return this->updateCCountQuestion(worldProxy, ctx);
        case PCountQuestion:
            return this->updatePCountQuestion(worldProxy, ctx);
        case DisplayResults:
            return this->updateDisplayResults(worldProxy, ctx);
    };
}

void GameState::CityInventory::render(WorldInteractionInterface *worldProxy, Window::window_ptr window)
{
    switch (this->state) {
        case CInventory:
            return this->renderCityInventory(worldProxy, window);
        case PInventory:
            return this->renderPlayerInventory(worldProxy, window);
        case CCountQuestion:
            return this->renderCCountQuestion(worldProxy, window);
        case PCountQuestion:
            return this->renderPCountQuestion(worldProxy, window);
        case DisplayResults:
            return this->renderDisplayResults(worldProxy, window);
    };
}

GameState::State *GameState::CityInventory::nextState()
{
    return NULL;
}

void GameState::CityInventory::clearNextState()
{

}

bool GameState::CityInventory::shouldClose()
{
    return this->inventoryShouldClose;
}

std::vector<std::string> GameState::CityInventory::getInventory(std::vector<Inventory::Record> inv)
{
    std::vector<std::string> v;
    int longestName = 0;
    for (int i = 0; i < inv.size(); ++i) {
        std::string name = ItemMap::get(inv[i].itemId).getName();
        if (name.size() > longestName) {
            longestName = name.size();
        }
    }
    for (int i = 0; i < inv.size(); ++i) {
        std::stringstream ss;
        Item item = ItemMap::get(inv[i].itemId);
        std::string pad;
        pad.resize((longestName + 2) - item.getName().size(), ' ');
        ss<<inv[i].count<<"\t"<<
            item.getBaseWorth()<<"\t"<<
            item.getWeight()<<"\t"<<
            item.getName()<<pad<<
            item.getDescription();
        v.push_back(ss.str());
    }
    return v;
}

void GameState::CityInventory::populateMenu(Component::Menu *menu, std::vector<std::string> options)
{
    std::string head = "cnt\tcost\twgt\tname\t\t\tdesc";
    *menu = Component::Menu(head, options, 10, 10, 20, 20);
}


void GameState::CityInventory::updateCityInventory(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    int result = this->cityInv.update(ctx);
    switch (result) {
        case -1:
            break;
        case -2:
            this->logger->debug("Back pressed");
            this->inventoryShouldClose = true;
            break;
        default:
            this->logger->debug("City: %d Selected", result);
            this->cityItemSelected = result;
            this->countInput = Component::TextInput("How Many: ", 5, 5);
            this->state = CCountQuestion;
            break;
    };
}

void GameState::CityInventory::updatePlayerInventory(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    int result = this->playerInv.update(ctx);
    switch (result) {
        case -1:
            break;
        case -2:
            this->logger->debug("Back pressed");
            this->state = CInventory;
            break;
        default:
            this->logger->debug("Player: %d Selected", result);
            this->playerItemSelected = result;
            this->countInput = Component::TextInput("How Many: ", 5, 5);
            this->state = PCountQuestion;
            break;
    };
}

// @todo: refactor
void GameState::CityInventory::updateCCountQuestion(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    std::string output = this->countInput.update(ctx);
    if (this->countInput.done()) {
        std::stringstream ss;
        ss.str(output);
        this->state = PInventory;
        ss>>this->cityCountSelected;
    }
}

void GameState::CityInventory::updatePCountQuestion(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    std::string output = this->countInput.update(ctx);
    if (this->countInput.done()) {
        std::stringstream ss;
        ss.str(output);
        this->state = DisplayResults;
        ss>>this->playerCountSelected;
    }
}

void GameState::CityInventory::updateDisplayResults(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    if (ctx->input == Input::ESCAPE) {
        this->inventoryShouldClose = true;
    }
}

void GameState::CityInventory::renderCityInventory(WorldInteractionInterface * worldProxy, Window::window_ptr window)
{

    int borderHeight = window->getHeight() * 0.1;
    int borderWidth = window->getWidth() * 0.1;
    this->cityInv.setDims(
        borderHeight, 
        borderWidth,
        window->getHeight() - (2 * borderHeight),
        window->getWidth() - (2 * borderWidth)
    );
    window->putstr(borderHeight - 1, borderWidth, this->city.getName(), 0);
    this->cityInv.render(window);
}

void GameState::CityInventory::renderPlayerInventory(WorldInteractionInterface * worldProxy, Window::window_ptr window)
{
    int borderHeight = window->getHeight() * 0.1;
    int borderWidth = window->getWidth() * 0.1;
    this->playerInv.setDims(
        borderHeight,
        borderWidth,
        window->getHeight() - (2 * borderHeight),
        window->getWidth() - (2 * borderWidth)
    );
    window->putstr(borderHeight - 1, borderWidth, this->player.getName(), 0);
    this->playerInv.render(window);
}

void GameState::CityInventory::renderCCountQuestion(WorldInteractionInterface * worldProxy, Window::window_ptr window)
{
    this->countInput.render(window);
}

void GameState::CityInventory::renderPCountQuestion(WorldInteractionInterface * worldProxy, Window::window_ptr window)
{
    this->countInput.render(window);
}

void GameState::CityInventory::renderDisplayResults(WorldInteractionInterface * worldProxy, Window::window_ptr window)
{
    std::stringstream ss;
    Item playerItem = ItemMap::get(
        player.getInventory()->getAt(playerItemSelected).itemId
    );
    Item cityItem = ItemMap::get(
        city.getInventory()->getAt(cityItemSelected).itemId
    );
    ss<<"Player chosen item: "<<playerItem.getName();
    window->putstr(5, 5, ss.str(), 0);
    ss.str("");
    ss<<"Player chosen count: "<<playerCountSelected;
    window->putstr(6, 5, ss.str(), 0);
    ss.str("");
    ss<<"City chosen item: "<<cityItem.getName();
    window->putstr(7, 5, ss.str(), 0);
    ss.str("");
    ss<<"City chosen count: "<<cityCountSelected;
    window->putstr(8, 5, ss.str(), 0);
    ss.str("");
}

