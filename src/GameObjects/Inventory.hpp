#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include "Globals.hpp"
#include "GameObjects/AbstractGameObject.hpp"
#include "GameObjects/Item.hpp"
#include "GameObjects/ItemMap.hpp"

class Inventory : public AbstractGameObject
{
public:
    struct Record {
        int count;
        int itemId;
        Record(int c, int i) : count(c), itemId(i) {}
    };

    Inventory();
    Inventory(const Inventory &other);
    Inventory(std::stringstream *ss);

    void fromStringStream(std::stringstream *ss);
    void toStringStream(std::stringstream *ss);

    void add(int itemId, int count);
    void add(Item item, int count);

    bool has(int itemId);
    Record get(int itemId);
    Record getAt(int index);
    
    std::vector<Record> getInv();
private:
    int find(int itemId);

    std::vector<Record> inv;
};

#endif //INVENTORY_HPP
