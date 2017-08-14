#ifndef ECONOMY_CITYTRADE_HPP
#define ECONOMY_CITYTRADE_HPP

#include "Services/WorldInteraction/WorldInteractionInterface.hpp"
#include "GameObjects/City.hpp"
#include "GameObjects/Player.hpp"
#include "GameObjects/Inventory.hpp"

#include "Services/Economy/General.hpp"

namespace Economy
{
    namespace CityTrade
    {
        bool willAcceptTrade(
            WorldInteractionInterface *worldProxy, 
            City *city, 
            Player *player,
            Inventory *playerStage,
            Inventory *cityStage
        );
    }
}

#endif //ECONOMY_CITYTRADE_HPP
