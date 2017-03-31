#ifndef LOCAL_WORLD_INTERACTION
#define LOCAL_WORLD_INTERACTION

#include <string>

#include "GameObjects/World.hpp"
#include "Screen.hpp"
#include "Services/WorldInteraction/WorldInteractionInterface.hpp"

/**
 * Manager for non-networked world interaction.
 */
class LocalWorldInteraction : virtual public WorldInteractionInterface, protected World
{
public:
    LocalWorldInteraction();
    LocalWorldInteraction(std::string worldName);

    void loadWorld();
    void draw(Screen &screen);
    void movePlayerToCoordinate(int y, int x);
    WorldChunk getChunk(int y, int x) const;
protected:
    int playerX;
    int playerY;

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
