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
    City(std::stringstream *ss);
    City(std::string name, int pos_x, int pos_y);
    void fromStringStream(std::stringstream *ss);
    void toStringStream(std::stringstream *ss);

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
