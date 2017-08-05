#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <sstream>

#include "Globals.hpp"
#include "GameObjects/AbstractGameObject.hpp"

/**
 * Item.
 * Any item which may be bought/sold/equipped in game.
 *
 * id must be unique as this will be a flyweight class, and inventories will
 * only hold ids to this class.
 * -1 signifies an uninitialized id, and will not be added to the ItemContainer
 */
class Item : public AbstractGameObject
{
public:
    Item();
    Item(int id, std::string name, std::string description, int weight, float baseWorth);
    Item(std::stringstream *ss);

    void fromStringStream(std::stringstream *ss);
    void toStringStream(std::stringstream *ss);

    int getId();
    std::string getName();
    std::string getDescription();
    int getWeight();
    float getBaseWorth();
private:
    int id;
    std::string name;
    std::string description;
    int weight;
    float baseWorth;
};

#endif //ITEM_HPP
