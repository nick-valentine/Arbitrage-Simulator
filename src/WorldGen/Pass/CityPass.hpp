#ifndef CITY_PASS_HPP
#define CITY_PASS_HPP

#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

#include "WorldGen/Pass/AbstractPass.hpp"
#include "GameObjects/ItemMap.hpp"

#include "Helpers/Vector.hpp"

#include "WorldGen/NoiseFunc.hpp"
#include "Services/Logger/Logger.hpp"

class CityPass : public AbstractPass
{
public:
    void init();

    void execute(World *world, boost::shared_ptr<Logger> logger);
    void doTile(int i, int j, Tile *tile, WorldChunk *chunk);

    AbstractPass *clone();

    std::string getName();
private:
    const static std::string name;
    static constexpr float cityConversionSpread = 50.0;
    static constexpr float cityConversionRatio = 0.125;
    static constexpr int minLivibility = 8;
    static constexpr int maxElevationDiff = 2;

    // when spawning a city, stop any cities from spawning within this radius of it
    static constexpr int citySpawnRadiusMask = 5;

    enum PassState {
        Gather = 0,
        Calc = 1,
        CityPlace = 2,
    };

    PassState state;

    void doGather(int i, int j, Tile *tile);
    void doPlace(int i, int j, Tile *tile, WorldChunk *chunk);

    void calcDifferentials();
    void calcAvgLivability();

    void convertTileToCity(int i, int j, Tile *tile, WorldChunk *chunk);

    std::vector< std::vector<int> > worldElevations;
    std::vector< std::vector<float> > worldDiff;
    std::vector< std::vector<bool> > citySpawnableMask;
    std::vector< std::vector<int> > livabilityMask;
    std::vector< std::vector<float> > avgLivabilityMask;

    NoiseFunc cityConversionNoise;
};

#endif //CITY_PASS_HPP

