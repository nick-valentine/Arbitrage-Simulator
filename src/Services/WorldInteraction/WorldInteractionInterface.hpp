#ifndef WORLD_INTERACTION_INTERFACE
#define WORLD_INTERACTION_INTERFACE

#include <boost/shared_ptr.hpp>

#include "GameObjects/World.hpp"
#include "GameObjects/Tile.hpp"
#include "Window/Window.hpp"

#include "Services/Logger/Logger.hpp"

/**
 * Class to proxy all interactions with the world through.
 * Proxy all world interactions through this class so that networked and local
 * gameplay can use a common interface and only differ in which class they
 * instantiate.
 */
class WorldInteractionInterface
{
public:
    virtual void loadWorld(boost::shared_ptr<Logger> logger) = 0;
    virtual void draw(Window::window_ptr window) = 0;
    virtual void movePlayerToCoordinate(int y, int x) = 0;
    virtual Tile getTileUnderPlayer() = 0;
    virtual City getCity(int y, int x) = 0;
private:
};

#endif //WORLD_INTERACTION_INTERFACE
