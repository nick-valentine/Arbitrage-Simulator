#include "WorldGen/Pass/TypePass.hpp"

const std::string TypePass::name = "Type";

void TypePass::init()
{
    this->typeNoise = NoiseFunc(TypePass::typeNoiseSpread);
}

void TypePass::doTile(int i, int j, Tile *tile)
{
    tile->setType(this->typeNoise.get(i, j));
}

AbstractPass *TypePass::clone()
{
    return new TypePass(*this);
}

std::string TypePass::getName()
{
    return TypePass::name;
}
