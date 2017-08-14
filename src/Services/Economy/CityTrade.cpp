#include "Services/Economy/CityTrade.hpp"

bool Economy::CityTrade::willAcceptTrade(
    WorldInteractionInterface *worldProxy, 
    City *city, 
    Player *player,
    Inventory *playerStage,
    Inventory *cityStage
)
{
    using namespace Economy::General;
    if (!inventoryAvailable(playerStage, player->getInventory())) {
        return false;
    }
    if (!inventoryAvailable(cityStage, city->getInventory())) {
        return false;
    }
    return true;
}
