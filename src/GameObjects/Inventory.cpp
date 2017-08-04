#include "GameObjects/Inventory.hpp"

Inventory::Inventory()
{
    this->inv = std::vector<Record>();
}

Inventory::Inventory(std::stringstream *ss)
{
    this->fromStringStream(ss);
}

void Inventory::fromStringStream(std::stringstream *ss)
{
    std::string line;
    std::getline((*ss), line, Globals::object_delimiter);
    std::stringstream lineSS;
    lineSS.str(line);
    while(lineSS.good()) {
        std::string id_str, count_str;
        int id, count;
        std::getline((lineSS), id_str, Globals::file_delimiter);
        std::getline((lineSS), count_str, Globals::file_delimiter);

        std::stringstream tempSS;
        tempSS.str(id_str);
        tempSS>>id;

        tempSS.str(std::string());
        tempSS.clear();

        tempSS.str(count_str);
        tempSS>>count;

        this->inv.push_back(Record(count, id));
    }
}

void Inventory::toStringStream(std::stringstream *ss)
{
    for (int i = 0; i < this->inv.size(); ++i) {
        (*ss)<<this->inv[i].count<<Globals::file_delimiter;
        (*ss)<<this->inv[i].itemId<<Globals::file_delimiter;
    }
    (*ss)<<Globals::object_delimiter;
}

void Inventory::add(int itemId, int count)
{
    int i = this->find(itemId);
    if (i == -1) {
        this->inv.push_back(Record(count, itemId));
    }
    this->inv[i].count += count;
}

void Inventory::add(Item item, int count)
{
    this->add(item.getId(), count);
}

Inventory::Record Inventory::get(int itemId)
{
    int i = this->find(itemId);
    if (i == -1) {
        return Inventory::Record(-1,-1);
    }
    return this->inv[i];
}

std::vector<Inventory::Record> Inventory::getInv()
{
    return this->inv;
}

int Inventory::find(int itemId)
{
    for (int i = 0; i < this->inv.size(); ++i) {
        if (this->inv[i].itemId == i) {
            return i;
        }
    }
    return -1;
}
