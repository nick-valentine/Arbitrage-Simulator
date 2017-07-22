#ifndef TYPE_PASS_HPP
#define TYPE_PASS_HPP

#include <string>

#include "WorldGen/Pass/AbstractPass.hpp"

#include "WorldGen/NoiseFunc.hpp"
#include "Services/Logger/Logger.hpp"

class TypePass : public AbstractPass
{
public:
    void init();
    void doTile(int i, int j, Tile *tile);

    AbstractPass *clone();

    std::string getName();
private:
    const static std::string name;

    static constexpr float typeNoiseSpread = 20.0;

    NoiseFunc typeNoise;
};

#endif //ELEVATION_PASS_HPP
