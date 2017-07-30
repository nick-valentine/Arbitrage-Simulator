#include "GameObjects/Item.hpp"

Item::Item()
{
    this->id = -1;
    this->name = "";
    this->description = "";
    this->weight = -1;
}

Item::Item(int id, std::string name, std::string description, int weight)
{
    this->id = id;
    this->name = name;
    this->description = description;
    this->weight = weight;
}

Item::Item(std::stringstream *ss)
{
    this->fromStringStream(ss);
}

void Item::fromStringStream(std::stringstream *ss)
{
    std::string id_str, weight_str;
    std::getline((*ss), id_str, Globals::file_delimiter);
    std::getline((*ss), this->name, Globals::file_delimiter);
    std::getline((*ss), this->description, Globals::file_delimiter);
    std::getline((*ss), weight_str, Globals::object_delimiter);

    std::stringstream temp_ss;
    temp_ss.str(id_str);
    temp_ss>>this->id;

    temp_ss.str(std::string());
    temp_ss.clear();

    temp_ss.str(weight_str);
    temp_ss>>this->weight;
}

void Item::toStringStream(std::stringstream *ss)
{
    (*ss)<<this->id<<Globals::file_delimiter;
    (*ss)<<this->name<<Globals::file_delimiter;
    (*ss)<<this->description<<Globals::file_delimiter;
    (*ss)<<this->weight<<Globals::object_delimiter;
}

int Item::getId()
{
    return this->id;
}

std::string Item::getName()
{
    return this->name;
}

std::string Item::getDescription()
{
    return this->description;
}

int Item::getWeight()
{
    return this->weight;
}
