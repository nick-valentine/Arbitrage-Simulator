#ifndef WORLD_INTERACTION_INTERFACE
#define WORLD_INTERACTION_INTERFACE

#include "GameObjects/World.hpp"
#include "Screen.hpp"

/**
 * Class to proxy all interactions with the world through.
 * Proxy all world interactions through this class so that networked and local
 * gameplay can use a common interface and only differ in which class they
 * instantiate.
 */
class WorldInteractionInterface
{
public:
    virtual void loadWorld() = 0;
    virtual void draw(Screen &screen) = 0;
    virtual void movePlayerToCoordinate(int y, int x) = 0;
private:
};

#endif //WORLD_INTERACTION_INTERFACE
