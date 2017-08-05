#include "WorldGen/Pass/CityPass.hpp"

const std::string CityPass::name = "Cities";

void CityPass::init()
{
    int height = WorldChunk::getChunkHeight() * World::getWorldHeight();
    int width = WorldChunk::getChunkWidth() * World::getWorldWidth();

    this->worldDiff = Vector::generateMask<float>(height, width);
    this->worldElevations = Vector::generateMask<int>(height, width);
    this->citySpawnableMask = Vector::generateMask<bool>(height, width);
    this->livabilityMask = Vector::generateMask<int>(height, width);
    this->avgLivabilityMask = Vector::generateMask<float>(height, width);

    this->cityConversionNoise = NoiseFunc(CityPass::cityConversionSpread);
}

void CityPass::execute(World *world, boost::shared_ptr<Logger> logger)
{
    logger->info("City Pass: Gathering world data");
    state = Gather;
    AbstractPass::execute(world, logger);

    logger->info("City Pass: Calculating world differentials");
    state = Calc;
    this->calcDifferentials();

    logger->info("City Pass: Calculating average livabilities");
    this->calcAvgLivability();

    logger->info("City Pass: Placing cities in suitable locations");
    state = CityPlace;
    AbstractPass::execute(world, logger);
}

void CityPass::doTile(int i, int j, Tile *tile, WorldChunk *chunk)
{
    switch (state) {
        case Gather:
            this->doGather(i, j, tile);
            break;
        case CityPlace:
            this->doPlace(i, j, tile, chunk);
            break;
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
    this->worldElevations[i][j] = tile->getElevation();
    this->citySpawnableMask[i][j] = tile->canConvertToCity();
    this->livabilityMask[i][j] = tile->getLivability();
}

void CityPass::doPlace(int i, int j, Tile *tile, WorldChunk *chunk)
{
    if (
        this->worldDiff[i][j] < CityPass::maxElevationDiff &&
        this->citySpawnableMask[i][j] == true &&
        this->avgLivabilityMask[i][j] > CityPass::minLivibility &&
        this->cityConversionNoise.get(i, j) > CityPass::cityConversionRatio
    ) {
        this->convertTileToCity(i, j, tile, chunk);
    }
}

void CityPass::calcDifferentials()
{
    for (int i = 1; i < this->worldElevations.size() - 1; ++i) {
        for (int j = 1; j < this->worldElevations[i].size() - 1; ++j) {
            this->worldDiff[i][j] = abs(this->worldElevations[i-1][j] - this->worldElevations[i+1][j]) *
                abs(this->worldElevations[i][j-1] - this->worldElevations[i][j+1])
            ;
        }
    }
}

void CityPass::calcAvgLivability()
{
    for (int i = 1; i < this->worldElevations.size() - 1; ++i) {
        for (int j = 1; j < this->worldElevations[i].size() - 1; ++j) {
            std::vector<float> tmp;
            tmp.push_back(this->livabilityMask[i-1][j-1]);
            tmp.push_back(this->livabilityMask[i-1][j]);
            tmp.push_back(this->livabilityMask[i-1][j+1]);
            tmp.push_back(this->livabilityMask[i][j-1]);
            tmp.push_back(this->livabilityMask[i][j]);
            tmp.push_back(this->livabilityMask[i][j+1]);
            tmp.push_back(this->livabilityMask[i+1][j-1]);
            tmp.push_back(this->livabilityMask[i+1][j]);
            tmp.push_back(this->livabilityMask[i+1][j+1]);
            this->avgLivabilityMask[i][j] = Vector::avg<float>(tmp);
        }
    }
}

void CityPass::convertTileToCity(int i, int j, Tile *tile, WorldChunk *chunk)
{
    //stop any cities from spawning nearby
    int startHeight = std::max(0, i - CityPass::citySpawnRadiusMask);
    int endHeight = std::min(int(this->citySpawnableMask.size()), i + CityPass::citySpawnRadiusMask);

    int startWidth = std::max(0, j - CityPass::citySpawnRadiusMask);
    int endWidth = std::min(int(this->citySpawnableMask[i].size()), j + CityPass::citySpawnRadiusMask);

    for (int y = startHeight; y < endHeight; ++y) {
        for (int x = startWidth; x < endWidth; ++x) {
            this->citySpawnableMask[y][x] = false;
        }
    }

    //convert tile
    tile->convertToCity();
    City city(
        City::city_name_starts[rand() % City::city_name_starts.size()] + 
        City::city_name_ends[rand() % City::city_name_ends.size()],
        j % WorldChunk::getChunkWidth(),
        i % WorldChunk::getChunkHeight()
    );

    // @todo: refactor inventory pass into it's own pass
    std::vector<int> ids = ItemMap::validIds();
    int itemsToGive = rand() % 20;
    for (int i = 0; i < itemsToGive; ++i) {
        city.addToInventory(
            ItemMap::get(
                ids[rand() % ids.size()]
            ).getId(),
            rand() % 15
        );
    }

    chunk->cities.push_back(city);
}

