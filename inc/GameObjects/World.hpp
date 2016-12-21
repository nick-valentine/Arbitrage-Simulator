#ifndef WORLD_HPP
#define WORLD_HPP

#include "GameObjects/WorldChunk.hpp"
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

    void fromStringStream(std::stringstream *ss);
    void toStringStream(std::stringstream *ss);

    void generateWorld();

    void draw(int playerY, int playerX);
private:
    static constexpr float elevationSkewNoiseSpread = 5.0;
    static constexpr float elevationNoiseSpread = 20.0;
    static constexpr float tileNoiseSpread = 6.0;

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
