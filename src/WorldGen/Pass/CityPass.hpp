#ifndef CITY_PASS_HPP
#define CITY_PASS_HPP

#include <vector>
#include <string>

#include "WorldGen/Pass/AbstractPass.hpp"

#include "WorldGen/NoiseFunc.hpp"
#include "Services/Logger/Logger.hpp"

class CityPass : public AbstractPass
{
public:
    void init();

    void execute(World *world, boost::shared_ptr<Logger> logger);
    void doTile(int i, int j, Tile *tile);

    AbstractPass *clone();

    std::string getName();
private:
    const static std::string name;

    enum PassState {
        Gather = 0
    };

    PassState state;

    void doGather(int i, int j, Tile *tile);

    std::vector< std::vector<float> > worldDiff;
};

#endif //CITY_PASS_HPP

