#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <curses.h>
#include <algorithm>
#include <vector>

#include "GameObjects/World.hpp"
#include "GameObjects/Player.hpp"

class Camera
{
public:
    Camera();
    Camera(unsigned int y, unsigned int x);
    void move(int y, int x);
    void moveTo(unsigned int y, unsigned int x);

    int getY() const;
    int getX() const;
    
    void render(Screen &screen, World &world, Player &player);
private:
    unsigned int pos_y;
    unsigned int pos_x;
};

#endif //CAMERA_HPP
