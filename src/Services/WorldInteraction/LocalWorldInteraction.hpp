#ifndef LOCAL_WORLD_INTERACTION
#define LOCAL_WORLD_INTERACTION

#include <string>
#include <boost/shared_ptr.hpp>

#include "GameObjects/World.hpp"
#include "Window/Window.hpp"
#include "Services/WorldInteraction/WorldInteractionInterface.hpp"

#include "Services/Logger/Logger.hpp"
#include "WorldGen/Generator.hpp"

/**
 * Manager for non-networked world interaction.
 */
class LocalWorldInteraction : virtual public WorldInteractionInterface, protected World
{
public:
    LocalWorldInteraction();
    LocalWorldInteraction(std::string worldName);

    void loadWorld(boost::shared_ptr<Logger> logger);
    void draw(Window::window_ptr window);
    void movePlayerToCoordinate(int y, int x);
    WorldChunk getChunk(int y, int x) const;
protected:
    int playerX;
    int playerY;

    Generator generator;

    /**
     * Convert the player's current global coordinates into a chunk, and
     * coordinates in that chunk.
     *
     * @param  int &chunkY
     * @param  int &chunkX
     * @param  int &Y
     * @param  int &X
     */
    void playerCoordinatesToChunkCoordinates(
        int &chunkY, int &chunkX, 
        int &Y, int &X
    );

    /**
     * convert global coordinates to into a chunk, and coordinates in that chunk.
     *
     * @param  int inY
     * @param  int inX
     * @param  int &chunkY
     * @param  int &chunkX
     * @param  int &outY
     * @param  int &outX
     */
    void globalCoordinatesToChunkCoordinates(
        int inY, int inX, 
        int &chunkY, int &chunkX, 
        int &outY, int &outX
    );
};

#endif //LOCAL_WORLD_INTERACTION
