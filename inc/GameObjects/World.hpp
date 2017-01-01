#ifndef WORLD_HPP
#define WORLD_HPP

#include "ConfigLoader.hpp"
#include "GameObjects/WorldChunk.hpp"
#include "GameObjects/Player.hpp"
#include "Screen.hpp"
#include "WorldGen/NoiseFunc.hpp"

#include <vector>
#include <string>
#include <sstream>
#include <time.h>

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

    void draw(Screen &screen, int playerY, int playerX);

    static int getWorldHeight();
    static int getWorldWidth();
private:
    static constexpr float elevationSkewNoiseSpread = 55.0;
    static constexpr float elevationNoiseSpread = 20.0;
    static constexpr float tileNoiseSpread = 6.0;

    static unsigned int worldHeight;
    static unsigned int worldWidth;
    int chunkHeight;
    int chunkWidth;

    void init();

    void spawnChunk(int y, int x);
    WorldChunk prepareChunk(int y, int x);

    std::vector< std::vector<WorldChunk> > chunks;
    std::string name;
    time_t creationTimestamp;
    
    NoiseFunc elevationSkewNoise;
    NoiseFunc elevationNoise;
    NoiseFunc tileNoise;
};

#endif //WORLD_HPP
