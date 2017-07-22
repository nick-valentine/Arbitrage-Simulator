#include "WorldGen/Pass/ElevationPass.hpp"


void ElevationPass::init()
{
    this->elevationSkewNoise = NoiseFunc(ElevationPass::elevationSkewNoiseSpread);
    this->elevationNoise = NoiseFunc(ElevationPass::elevationNoiseSpread);
}

void ElevationPass::doTile(int i, int j, Tile *tile)
{
    tile->myElevation = this->elevationMap(
        elevationNoise.get(i, j),
        elevationSkewNoise.get(i, j)
    );
}

float ElevationPass::elevationMap(float input, float skew)
{
    float x = 1.0f - pow(2.00f, -(0.75f) * (input + 0.90));
    x += x*skew;
    return x;
}
