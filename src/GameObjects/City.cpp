#include "GameObjects/City.hpp"

City::City()
{
    this->name = "";
    this->pos_x = 0;
    this->pos_y = 0;
}

City::City(std::stringstream *ss)
{
    this->fromStringStream(ss);
}

void City::fromStringStream(std::stringstream *ss)
{
    std::string pos_x_str, pos_y_str;
    std::getline((*ss), this->name, Globals::file_delimeter);
    std::getline((*ss), pos_x_str, Globals::file_delimeter);
    std::getline((*ss), pos_y_str);

    std::stringstream temp_ss;
    temp_ss.str(pos_x_str);
    temp_ss>>this->pos_x;

    temp_ss.str(std::string());
    temp_ss.clear();

    temp_ss.str(pos_y_str);
    temp_ss>>this->pos_y;
}

void City::toStringStream(std::stringstream *ss)
{
    (*ss)<<this->name<<Globals::file_delimeter
        <<this->pos_x<<Globals::file_delimeter
        <<this->pos_y<<Globals::object_delimiter;
}

void City::setName(std::string name)
{
    this->name = name;
}

const std::string& City::getName() const
{
    return this->name;
}

void City::setPosX(int x)
{
    this->pos_x = x;
}

int City::getPosX() const
{
    return this->pos_x;
}

void City::setPosY(int y)
{
    this->pos_y = y;
}

int City::getPosY() const
{
    return this->pos_y;
}
