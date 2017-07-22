#include "WorldGen/Pass/ElevationPass.hpp"

const std::string ElevationPass::name = "Elevation";

void ElevationPass::init()
{
    this->elevationSkewNoise = NoiseFunc(ElevationPass::elevationSkewNoiseSpread);
    this->elevationNoise = NoiseFunc(ElevationPass::elevationNoiseSpread);
}

void ElevationPass::doTile(int i, int j, Tile *tile)
{
    tile->setElevation(
       this->elevationMap(
            elevationNoise.get(i, j),
            elevationSkewNoise.get(i, j)
        )
    );
}

std::string ElevationPass::getName()
{
    return ElevationPass::name;
}

AbstractPass *ElevationPass::clone()
{
    return new ElevationPass(*this);
}

float ElevationPass::elevationMap(float input, float skew)
{
    float x = 1.0f - pow(2.00f, -(0.75f) * (input + 0.90));
    x += x*skew;
    return abs(x * (float)Tile::elevationMax);
}

