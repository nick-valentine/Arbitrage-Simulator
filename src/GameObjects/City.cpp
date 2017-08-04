#include "GameObjects/City.hpp"

const std::string City::city_name_file_path = "GameData/city_names.txt";

std::vector<std::string> City::city_name_starts = std::vector<std::string>();
std::vector<std::string> City::city_name_ends = std::vector<std::string>();

City::City()
{
    this->name = "";
    this->pos_x = 0;
    this->pos_y = 0;
    this->inv = Inventory();
}

City::City(const City &other)
{
    this->name = other.name;
    this->pos_x = other.pos_x;
    this->pos_y = other.pos_y;
    this->inv = other.inv;
}

City::City(std::string name, int pos_x, int pos_y)
{
    this->name = name;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->inv = Inventory();
}

City::City(std::stringstream *ss)
{
    this->name = "";
    this->pos_x = 0;
    this->pos_y = 0;
    this->inv = Inventory();
    this->fromStringStream(ss);
}

void City::fromStringStream(std::stringstream *ss)
{
    std::string pos_x_str, pos_y_str;
    std::getline((*ss), this->name, Globals::file_delimiter);
    std::getline((*ss), pos_x_str, Globals::file_delimiter);
    std::getline((*ss), pos_y_str, Globals::object_delimiter);
    this->inv.fromStringStream(ss);

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
    (*ss)<<this->name<<Globals::file_delimiter
        <<this->pos_x<<Globals::file_delimiter
        <<this->pos_y<<Globals::object_delimiter;
    this->inv.toStringStream(ss);
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

void City::addToInventory(int itemId, int count)
{
    this->inv.add(itemId, count);
}

Inventory City::getInventory()
{
    return this->inv;
}

void City::load_city_names()
{
    std::ifstream ifile;
    ifile.open(City::city_name_file_path.c_str());
    std::string type, name;
    while(ifile.good()) {
        ifile>>type>>name;
        if(type == "start") {
            city_name_starts.push_back(name);
        } else if(type == "end") {
            city_name_ends.push_back(name);
        }
    }    
    ifile.close();
}
