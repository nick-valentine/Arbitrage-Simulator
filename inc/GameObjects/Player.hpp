#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <sstream>

#include "Screen.hpp"
#include "GameObjects/AbstractGameObject.hpp"

class Player : public AbstractGameObject
{
public:
    Player();
    Player(std::string name, int y, int x);
    Player(std::stringstream *ss);

    void fromStringStream(std::stringstream *ss);
    void toStringStream(std::stringstream *ss);

    void move(int y, int x);
    void getYX(int &y, int &x);

    void draw(Screen &screen, int offsetTop, int offsetLeft);
private:
    static const char representation = 'P';

    std::string name;
    int y;
    int x;
};

#endif //PLAYER_HPP
