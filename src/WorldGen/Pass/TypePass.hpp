#ifndef TYPE_PASS_HPP
#define TYPE_PASS_HPP

#include "WorldGen/Pass/AbstractPass.hpp"

#include "WorldGen/NoiseFunc.hpp"

class TypePass : public AbstractPass
{
public:
    void init();
    void doTile(int i, int j, Tile *tile);
private:
    static constexpr float typeNoiseSpread = 20.0;

    NoiseFunc typeNoise;
};

#endif //ELEVATION_PASS_HPP
