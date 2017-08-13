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
    if (this->state == CInventory) {
        this->updateCityInventory(worldProxy, ctx);
    } else if (this->state == PInventory) {
        this->updatePlayerInventory(worldProxy, ctx);
    }
}

void GameState::CityInventory::render(WorldInteractionInterface *worldProxy, Window::window_ptr window)
{
    int borderHeight = window->getHeight() * 0.1;
    int borderWidth = window->getWidth() * 0.1;
    int halfHeight = window->getHeight() / 2;
    this->cityInv.setDims(
        borderHeight, 
        borderWidth,
        halfHeight - borderHeight,
        window->getWidth() - (2 * borderWidth)
    );

    this->playerInv.setDims(
        halfHeight + 3,
        borderWidth,
        halfHeight - (2 * borderHeight) - 3,
        window->getWidth() - (2 * borderWidth)
    );
    window->putstr(halfHeight + 2, borderWidth, this->player.getName(), 0);
    window->putstr(borderHeight - 2, borderWidth, this->city.getName(), 0);
    this->cityInv.render(window);
    this->playerInv.render(window);
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
    if (ctx->input == Input::ESCAPE) {
        this->state = PInventory;
    }
    int result = this->cityInv.update(ctx);
    switch (result) {
        case -1:
            break;
        case -2:
            this->logger->debug("Back pressed");
            this->msgDown = -1;
            this->inventoryShouldClose = true;
            break;
        default:
            this->logger->debug("%d Selected", result);
            this->msgDown = result;
            this->inventoryShouldClose = true;
            break;
    };
}

void GameState::CityInventory::updatePlayerInventory(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    if (ctx->input == Input::ESCAPE) {
        this->state = CInventory;
    }
    int result = this->playerInv.update(ctx);
    switch (result) {
        case -1:
            break;
        case -2:
            this->logger->debug("Back pressed");
            this->msgDown = -1;
            this->inventoryShouldClose = true;
            break;
        default:
            this->logger->debug("%d Selected", result);
            this->msgDown = result;
            this->inventoryShouldClose = true;
            break;
    };
}


