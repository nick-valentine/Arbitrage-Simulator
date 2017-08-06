#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <sstream>

#include "Window/Window.hpp"
#include "GameObjects/AbstractGameObject.hpp"

/**
 * Player.
 * A player controlled avatar, could be controlled via keyboard, or network
 * replication.
 *
 * @todo: allow for one of several representations and colors
 */
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
    std::string getName();

    void draw(Window::window_ptr window, int offsetTop, int offsetLeft);
private:
    static const char representation = 'P';

    std::string name;
    int y;
    int x;
};

#endif //PLAYER_HPP
