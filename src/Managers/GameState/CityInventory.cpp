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
    if (ctx->input == Input::ENTER && this->state != CountQuestion) {
        this->state = DisplayResults;
    }
    switch (this->state) {
        case CInventory:
            return this->updateCityInventory(worldProxy, ctx);
        case PInventory:
            return this->updatePlayerInventory(worldProxy, ctx);
        case CountQuestion: return this->updateCountQuestion(worldProxy, ctx);
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
        case CountQuestion:
            return this->renderCountQuestion(worldProxy, window);
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
    if (ctx->input == Input::RIGHT || ctx->input == Input::LEFT) {
        this->state = PInventory;
    }
    this->stageFor = c;
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
            this->itemStage = this->city.getInventory()->getInv()[result].itemId;
            this->countInput = Component::TextInput("How Many: ", 5, 5);
            this->state = CountQuestion;
            this->lastState = CInventory;
            break;
    };
}

void GameState::CityInventory::updatePlayerInventory(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    if (ctx->input == Input::RIGHT || ctx->input == Input::LEFT) {
        this->state = CInventory;
    }
    this->stageFor = p;
    int result = this->playerInv.update(ctx);
    switch (result) {
        case -1:
            break;
        case -2:
            this->logger->debug("Back pressed");
            this->inventoryShouldClose = true;
            break;
        default:
            this->logger->debug("Player: %d Selected", result);
            this->itemStage = this->player.getInventory()->getInv()[result].itemId;
            this->countInput = Component::TextInput("How Many: ", 5, 5);
            this->state = CountQuestion;
            this->lastState = PInventory;
            break;
    };
}

void GameState::CityInventory::updateCountQuestion(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    std::string output = this->countInput.update(ctx);
    if (this->countInput.done()) {
        std::stringstream ss;
        ss.str(output);
        this->state = this->lastState;
        ss>>this->countStage;
        if (this->stageFor == p) {
            this->playerStage.add(this->itemStage, this->countStage);
        } else if (this->stageFor == c) {
            this->cityStage.add(this->itemStage, this->countStage);
        }
        this->itemStage = 0;
        this->countStage = 0;
    }
}

void GameState::CityInventory::updateDisplayResults(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    if (ctx->input == Input::ESCAPE) {
        this->inventoryShouldClose = true;
    } else if (ctx->input == Input::ENTER) {
        if (Economy::CityTrade::willAcceptTrade(
            (*worldProxy), 
            &this->city,
            &this->player,
            &this->playerStage,
            &this->cityStage
        )) {
            this->logger->debug("Trade accepted");
        } else {
            this->logger->debug("Get lost");
        }
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

void GameState::CityInventory::renderCountQuestion(WorldInteractionInterface * worldProxy, Window::window_ptr window)
{
    this->countInput.render(window);
}

void GameState::CityInventory::renderDisplayResults(WorldInteractionInterface * worldProxy, Window::window_ptr window)
{
    int borderHeight = window->getHeight() * 0.1;
    int borderWidth = window->getWidth() * 0.1;
    int halfWidth = window->getWidth() / 2;

    window->putstr(borderHeight - 1, borderWidth, this->player.getName(), 0);
    std::vector<Inventory::Record> pInv = this->playerStage.getInv();
    for (int i = 0; i < pInv.size(); ++i) {
        this->displayItem(window, pInv[i], borderHeight + i, borderWidth);
    }
    window->putstr(borderHeight - 1, halfWidth, this->city.getName(), 0);
    std::vector<Inventory::Record> cInv = this->cityStage.getInv();
    for (int i = 0; i < cInv.size(); ++i) {
        this->displayItem(window, cInv[i], borderHeight + i, halfWidth);
    }
}

void GameState::CityInventory::displayItem(Window::window_ptr window, Inventory::Record rec, int y, int x)
{
    std::stringstream ss;
    Item i = ItemMap::get(rec.itemId);
    ss<<rec.count<<"\t"<<i.getName();
    window->putstr(y, x, ss.str(), 0);
}
