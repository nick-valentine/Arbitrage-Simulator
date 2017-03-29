#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <curses.h>
#include <algorithm>
#include <vector>

#include "Services/WorldInteraction/WorldInteractionInterface.hpp"
#include "GameObjects/Player.hpp"

/**
 * Viewport for drawing the world and player modified by own position.
 */
class Camera
{
public:
    Camera();
    Camera(unsigned int y, unsigned int x);
    void move(int y, int x);
    void moveTo(unsigned int y, unsigned int x);

    int getY() const;
    int getX() const;
    
    /**
     * Render the world and player onto the screen
     *
     * @param  Screen &screen
     * @param  WorldInteractionInterface  &world
     * @param  Player &player
     */
    void render(Screen &screen, WorldInteractionInterface &worldProxy, Player &player);
private:
    unsigned int pos_y;
    unsigned int pos_x;
};

#endif //CAMERA_HPP
