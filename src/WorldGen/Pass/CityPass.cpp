#include "WorldGen/Pass/CityPass.hpp"

const std::string CityPass::name = "Cities";

void CityPass::init()
{
    this->worldDiff = std::vector< std::vector<float> >();
}

void CityPass::execute(World *world, boost::shared_ptr<Logger> logger)
{
    logger->info("Gathering world data");
    state = Gather;
    AbstractPass::execute(world, logger);
    logger->info("Done gathering world data");
}

void CityPass::doTile(int i, int j, Tile *tile)
{
    switch (state) {
        case Gather:
            this->doGather(i, j, tile);
    };
}

std::string CityPass::getName()
{
    return CityPass::name;
}

AbstractPass *CityPass::clone()
{
    return new CityPass(*this);
}

void CityPass::doGather(int i, int j, Tile *tile)
{

}
