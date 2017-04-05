#include "GameObjects/Player.hpp"

Player::Player()
{
    this->name = "";
    this->x = 0;
    this->y = 0;
}

Player::Player(std::string name, int y, int x)
{
    this->name = name;
    this->y = y;
    this->x = x;
}

Player::Player(std::stringstream *ss)
{
    this->fromStringStream(ss);
}

void Player::fromStringStream(std::stringstream *ss)
{
    (*ss)>>this->name>>this->y>>this->x;
}

void Player::toStringStream(std::stringstream *ss)
{
    (*ss)<<this->name<<" ";
    (*ss)<<this->y<<" ";
    (*ss)<<this->x<<" ";
}

void Player::move(int y, int x)
{
    this->y += y;
    this->x += x;
}

void Player::getYX(int &y, int &x)
{
    y = this->y;
    x = this->x;
}

void Player::draw(GameWindow &window, int offsetTop, int offsetLeft)
{
    window.put(
        /* color pair */ 0, 
        /* layer */ 10,
        Player::representation,
        window.getHeight() / 2,
        window.getWidth() / 2 
    );
}
