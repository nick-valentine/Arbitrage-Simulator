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
    this->inventory = Component::Menu("", this->options, 10, 10, 20, 20);
    this->inventoryShouldClose = false;
    this->getCityInventory(&this->city);
    this->populateMenu(&this->inventory, this->cityInventoryOptions);
}

void GameState::CityInventory::setCity(City city)
{
    this->city = city;
    this->getCityInventory(&this->city);
    this->populateMenu(&this->inventory, this->cityInventoryOptions);
}

void GameState::CityInventory::update(WorldInteractionInterface ** worldProxy, Context *ctx)
{
    int result = this->inventory.update(ctx);
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

void GameState::CityInventory::render(WorldInteractionInterface *worldProxy, Window::window_ptr window)
{
    int borderHeight = window->getHeight() * 0.1;
    int borderWidth = window->getWidth() * 0.1;
    this->inventory.setDims(
        borderHeight, 
        borderWidth,
        window->getHeight() - (2 * borderHeight),
        window->getWidth() - (2 * borderWidth)
    );
    this->inventory.render(window);
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

void GameState::CityInventory::getCityInventory(City *city)
{
    this->cityInventory = city->getInventory().getInv();
    this->cityInventoryOptions = std::vector<std::string>();
    int longestName = 0;
    for (int i = 0; i < this->cityInventory.size(); ++i) {
        std::string name = ItemMap::get(this->cityInventory[i].itemId).getName();
        if (name.size() > longestName) {
            longestName = name.size();
        }
    }
    for (int i = 0; i < this->cityInventory.size(); ++i) {
        std::stringstream ss;
        Item item = ItemMap::get(this->cityInventory[i].itemId);
        std::string pad;
        pad.resize((longestName + 2) - item.getName().size(), ' ');
        ss<<this->cityInventory[i].count<<"\t"<<
            item.getBaseWorth()<<"\t"<<
            item.getWeight()<<"\t"<<
            item.getName()<<pad<<
            item.getDescription();
        this->cityInventoryOptions.push_back(ss.str());

    }
}

void GameState::CityInventory::populateMenu(Component::Menu *menu, std::vector<std::string> options)
{
    std::string head = "cnt\tcost\twgt\tname\t\t\tdesc";
    this->inventory = Component::Menu(head, options, 10, 10, 20, 20);
}
