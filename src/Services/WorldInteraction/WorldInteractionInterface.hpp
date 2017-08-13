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
    virtual bool loadWorld(boost::shared_ptr<Logger> logger) = 0;
    virtual void cleanup() = 0;
    virtual void draw(Window::window_ptr window, int offsetTop, int offsetLeft) = 0;
    virtual void movePlayer(int index, int y, int x) = 0;
    virtual Tile getTileUnderPlayer(int index) = 0;
    virtual City getCity(int y, int x) = 0;
    virtual int getPlayer(std::string name) = 0;
    virtual Player playerInfo(int index) = 0;
private:
};

#endif //WORLD_INTERACTION_INTERFACE
