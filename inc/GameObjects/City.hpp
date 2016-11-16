#ifndef CITY_HPP
#define CITY_HPP

#include <sstream>
#include <string>

#include "Globals.hpp"
#include "GameObjects/AbstractGameObject.hpp"

class City : public AbstractGameObject
{
public:
    City(std::istringstream *iss);
    void fromStringStream(std::istringstream *iss);
    void toStringStream(std::ostringstream *oss);

private:
    City();

    std::string name;
    int pos_x;
    int pos_y;
};

#endif //CITY_HPP
