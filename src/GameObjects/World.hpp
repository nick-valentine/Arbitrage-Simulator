#ifndef WORLD_HPP
#define WORLD_HPP

#include <mutex>
#include <vector>
#include <string>
#include <sstream>
#include <time.h>

#include "ConfigLoader.hpp"
#include "GameObjects/WorldChunk.hpp"
#include "GameObjects/Player.hpp"
#include "Window/Window.hpp"

/**
 * World.
 * Owner of all game objects.
 * The world is composed of many world chunks that can be individually
 * replicated. Should be treated as a buffer transfer object, or a source of
 * truth only, applicatinlogic shuld not go here.
 */
class World
{
public:
    World();
    World(std::stringstream *ss);
    World(std::string name);
    static void configure();

    void fromStringStream(std::stringstream *ss);
    void toStringStream(std::stringstream *ss);

    void generateWorld();

    void draw(Window::window_ptr window, int playerY, int playerX);

    static int getWorldHeight();
    static int getWorldWidth();

    static unsigned int worldHeight;
    static unsigned int worldWidth;
    int chunkHeight;
    int chunkWidth;

    //Y major, X inner
    std::vector< std::vector<WorldChunk> > chunks;
    std::string name;
    time_t creationTimestamp;

    std::mutex worldProtect;

    /**
     * Initialize.
     * Setup required variables and state before object can be used.
     * @todo: when adding saving and loading world, the noise functions will
     *        have to be added to the get from and add to stringstream functions.
     */
    void init();

    /**
     * Spawn a chunk at x,y.
     * This is actually sort of a misnomer, having a chunk at x,y requires
     * chunks at all positions smaller than x,y, so this function expands the
     * chunk grid  to x,y spawning chunks to fill the gaps.
     *
     * @param  int y y position in the grid to add a worldChunk
     * @param  int x x position in the grid to add a worldChunk
     */
    void spawnChunk(int y, int x);

    /**
     * Prepare Chunk.
     * Factory method for world chunks.
     *
     * @param  int y y location in the noise functions to use
     * @param  int x x location in the noise funcitons to use
     * @return WorldChunk
     */
    WorldChunk prepareChunk(int y, int x);
};

#endif //WORLD_HPP
