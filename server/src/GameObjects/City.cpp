#include "GameObjects/City.hpp"

City::City(std::istringstream *iss)
{
    this->fromStringsStream(iss);
}

void City::fromStringStream(std::istringstream *iss)
{
    std::getline((*iss), this->name, Globals::file_delimeter);
    std::getline((*iss), this->pos_x, Globals::file_delimeter);
    std::getline((*iss), this->pos_y, Globals::file_delimeter);
}

void City::toStringStream(std::ostringstream *oss)
{
    (*oss)<<this->name<<Globals::file_delimeter
        <<this->pos_x<<Globals::file_delimeter
        <<this->pos_y<<Globals::file_delimeter;
}
