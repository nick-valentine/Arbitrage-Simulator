#include "WorldGen/Pass/TypePass.hpp"

void TypePass::init()
{
    this->typeNoise = NoiseFunc(TypePass::typeNoiseSpread);
}

void TypePass::doTile(int i, int j, Tile *tile)
{
    tile->setType(this->typeNoise.get(i, j));
}
