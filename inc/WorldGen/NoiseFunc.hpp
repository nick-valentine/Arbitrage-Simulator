#ifndef NOISEFUNC_HPP
#define NOISEFUNC_HPP

#include <stdlib.h>
#include <vector>
#include <utility>
#include <sstream>

class NoiseFunc
{
public:
    NoiseFunc();
    NoiseFunc(std::stringstream *ss);
    NoiseFunc(float gridPeriod);

    void fromStringStream(std::stringstream *ss);
    void toStringStream(std::stringstream *ss);

    float getRaw(float x, float y);
    float get(int x, int y);
private:
    static const unsigned int rand_steps = 1024;

    float perlin(float x, float y); 
    float dotGridGradient(int ix, int iy, float x, float y);
    float lerp(float a0, float a1, float w = 0.5);

    void addGridGradient(int x, int y);

    float newRand();
    std::pair<float, float> newRandPair();

    float gridPeriod;
    std::vector< std::vector< std::pair< float, float > > > Grid;
};

#endif //NOISEFUNC_HPP
