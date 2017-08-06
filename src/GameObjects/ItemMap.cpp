#include "GameObjects/ItemMap.hpp"

const std::string ItemMap::filename = "GameData/items.txt";
std::map<int, Item> ItemMap::collection = std::map<int, Item>();

void ItemMap::init(Logger::LoggerPtr logger)
{
    logger->info("Starting loading items");
    std::ifstream ifile;
    ifile.open(ItemMap::filename.c_str());
    while (ifile.good()) {
        std::string buff;
        std::getline(ifile, buff);
        if (buff == "") {
            continue;
        }
        std::stringstream ss;
        ss.str(buff);
        Item item(&ss);
        if (ItemMap::collection.find(item.getId()) == ItemMap::collection.end()) {
            ItemMap::collection[item.getId()] = item;
            logger->info(
                "Loaded item %d:%s; %s, with weight: %i, and base worth: %f", 
                item.getId(),
                item.getName().c_str(),
                item.getDescription().c_str(),
                item.getWeight(),
                item.getBaseWorth()
            );
        } else {
            logger->error("Two items have the same id of %i", item.getId());
        }
    }
    logger->info("Done loading items");
}

void ItemMap::fromStringStream(std::stringstream *ss)
{
    while ((*ss).good()) {
        std::string buff;
        std::getline((*ss), buff, Globals::object_delimiter);
        std::stringstream tmpSS;
        tmpSS.str(buff);
        Item item(&tmpSS);
        if (ItemMap::collection.find(item.getId()) == ItemMap::collection.end()) {
            ItemMap::collection[item.getId()] = item;
        }
    }
}

void ItemMap::toStringStream(std::stringstream *ss)
{
    for (int i = 0; i < ItemMap::collection.size(); ++i) {
        ItemMap::collection[i].toStringStream(ss);
    }
}

Item ItemMap::get(int id)
{
    return ItemMap::collection[id];
}

std::vector<int> ItemMap::validIds()
{
    std::vector<int> ids;
    auto it = ItemMap::collection.begin();
    for (; it != ItemMap::collection.end(); it++) {
        ids.push_back(it->first);
    }
    return ids;
}
