#ifndef ECONOMY_GENERAL_HPP
#define ECONOMY_GENERAL_HPP

#include "GameObjects/Inventory.hpp"

namespace Economy
{
    namespace General
    {
        bool inventoryAvailable(
            Inventory *stage,
            Inventory *takeFrom
        );
    }
}

#endif //ECONOMY_GENERAL_HPP
