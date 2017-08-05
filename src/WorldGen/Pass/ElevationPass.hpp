#ifndef ELEVATION_PASS_HPP
#define ELEVATION_PASS_HPP

#include <string>

#include "WorldGen/Pass/AbstractPass.hpp"

#include "WorldGen/NoiseFunc.hpp"
#include "Services/Logger/Logger.hpp"

class ElevationPass : public AbstractPass
{
public:
    void init();
    void doTile(int i, int j, Tile *tile, WorldChunk *chunk);

    AbstractPass *clone();

    std::string getName();
private:
    const static std::string name;

    float elevationMap(float input, float skew);

    static constexpr float elevationSkewNoiseSpread = 55.0;
    static constexpr float elevationNoiseSpread = 20.0;

    NoiseFunc elevationSkewNoise;
    NoiseFunc elevationNoise;
};

#endif //ELEVATION_PASS_HPP
