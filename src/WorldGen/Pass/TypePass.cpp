#include "WorldGen/Pass/TypePass.hpp"

const std::string TypePass::name = "Type";

void TypePass::init()
{
    this->typeNoise = NoiseFunc(TypePass::typeNoiseSpread);
}

void TypePass::doTile(int i, int j, Tile *tile, WorldChunk *chunk)
{
    tile->setType(
        this->typeMap(
            tile,
            this->typeNoise.get(i, j)
        )
    );
}

AbstractPass *TypePass::clone()
{
    return new TypePass(*this);
}

std::string TypePass::getName()
{
    return TypePass::name;
}

int TypePass::typeMap(Tile *tile, float tileInput)
{
    std::vector<int> typesAllowedAtThisElevation;
    for(int i = 0; i < Tile::allowedSpawnCount; ++i) {
        unsigned int min = Tile::Tiles[Tile::AllowedSpawns[i]].elevationMin;
        unsigned int max = Tile::Tiles[Tile::AllowedSpawns[i]].elevationMax;
        if(tile->getElevation() >= min && tile->getElevation() <= max) {
            typesAllowedAtThisElevation.push_back(Tile::AllowedSpawns[i]);
        }
    }
    if(typesAllowedAtThisElevation.size() == 0) {
        std::cout<<"ERROR: Can not spawn tile at elevation "<<tile->getElevation()<<std::endl;
        exit(1);
    }

    float tileType = tileInput;
    tileType *= TypePass::veryLargeMultiplyer;
    int indexType = abs((int)tileType);
    indexType %= typesAllowedAtThisElevation.size();
    int type = typesAllowedAtThisElevation[indexType];

    return type;
}
