#include "Camera.hpp"

Camera::Camera()
{
    this->pos_y = 0;
    this->pos_x = 0;
}

Camera::Camera(unsigned int y, unsigned int x)
{
    this->pos_y = y;
    this->pos_x = x;
}

void Camera::move(int y, int x)
{
    this->pos_y = std::max((unsigned int)0, this->pos_y + y);
    this->pos_x = std::max((unsigned int)0, this->pos_x + x);
}

void Camera::moveTo(unsigned int y, unsigned int x)
{
    this->pos_y = y;
    this->pos_x = x;
}

int Camera::getY() const
{
    return this->pos_y;
}

int Camera::getX() const
{
    return this->pos_x;
}

void Camera::render(Screen &screen, WorldInteractionInterface &worldProxy, Player &player)
{
    worldProxy.draw(screen);
    player.draw(screen, this->pos_y, this->pos_x);
}
