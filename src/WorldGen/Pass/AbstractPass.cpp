#include "WorldGen/Pass/AbstractPass.hpp"

std::vector< std::vector<WorldChunk> > AbstractPass::getChunks(World *world)
{
    return world->chunks;
}

void AbstractPass::setChunks(World *world, std::vector< std::vector<WorldChunk> > chunks)
{
    world->chunks = chunks;
}

unsigned int AbstractPass::getWorldHeight()
{
    return World::worldHeight;
}

unsigned int AbstractPass::getWorldWidth()
{
    return World::worldWidth;
}

int AbstractPass::getChunkHeight(World *world)
{
    return world->chunkHeight;
}

int AbstractPass::getChunkWidth(World *world)
{
    return world->chunkWidth;
}
