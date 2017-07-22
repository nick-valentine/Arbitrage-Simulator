#ifndef ELEVATION_PASS_HPP
#define ELEVATION_PASS_HPP

#include "WorldGen/Pass/AbstractPass.hpp"

#include "WorldGen/NoiseFunc.hpp"

class ElevationPass : public AbstractPass
{
public:
    void init();
    void doTile(int i, int j, Tile *tile);
private:
    float elevationMap(float input, float skew);

    static constexpr float elevationSkewNoiseSpread = 55.0;
    static constexpr float elevationNoiseSpread = 20.0;

    NoiseFunc elevationSkewNoise;
    NoiseFunc elevationNoise;
};

#endif //ELEVATION_PASS_HPP
