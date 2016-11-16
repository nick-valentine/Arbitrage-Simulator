#ifndef CITY_HPP
#define CITY_HPP

#include <sstream>
#include <string>

#include "Globals.hpp"
#include "GameObjects/AbstractGameObject.hpp"

class City : public AbstractGameObject
{
public:
    City();
    City(std::istringstream *iss);
    void fromStringStream(std::istringstream *iss);
    void toStringStream(std::ostringstream *oss);

    void setName(std::string name);
    const std::string& getName() const;

    void setPosX(int x);
    int getPosX() const;

    void setPosY(int y);
    int getPosY() const;
private:
    std::string name;
    int pos_x;
    int pos_y;
};

#endif //CITY_HPP
