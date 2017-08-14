#include "Services/Economy/General.hpp"

bool Economy::General::inventoryAvailable(
    Inventory *stage,
    Inventory *takeFrom
)
{
    auto s = stage->getInv();
    for (int i = 0; i < s.size(); ++i) {
        if (takeFrom->has(s[i].itemId)) {
            auto r = takeFrom->get(s[i].itemId);
            if (r.count < s[i].count) {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}
