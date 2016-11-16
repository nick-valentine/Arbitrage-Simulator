#include "GameObjects/City.hpp"

City::City(std::istringstream *iss)
{
    this->fromStringStream(iss);
}

void City::fromStringStream(std::istringstream *iss)
{
    std::string pos_x_str, pos_y_str;
    std::getline((*iss), this->name, Globals::file_delimeter);
    std::getline((*iss), pos_x_str, Globals::file_delimeter);
    std::getline((*iss), pos_y_str, Globals::file_delimeter);

    std::stringstream ss;
    ss.str(pos_x_str);
    ss>>this->pos_x;
    ss.str(pos_y_str);
    ss>>this->pos_y;
}

void City::toStringStream(std::ostringstream *oss)
{
    (*oss)<<this->name<<Globals::file_delimeter
        <<this->pos_x<<Globals::file_delimeter
        <<this->pos_y<<Globals::file_delimeter;
}
