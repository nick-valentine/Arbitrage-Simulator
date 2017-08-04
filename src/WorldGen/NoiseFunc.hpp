#ifndef NOISEFUNC_HPP
#define NOISEFUNC_HPP

#include <stdlib.h>
#include <vector>
#include <utility>
#include <sstream>
#include <time.h>

/**
 * Noise Function Based on Perlin Noise.
 */
class NoiseFunc
{
public:
    NoiseFunc();
    NoiseFunc(std::stringstream *ss);
    NoiseFunc(float gridPeriod);

    void fromStringStream(std::stringstream *ss);
    void toStringStream(std::stringstream *ss);

    /**
     * Get the return of this noise function not modified by gridPeriod.
     *
     * @param  float x x position in grid to get noise at
     * @param  float y y position in grid to get noise at
     */
    float getRaw(float x, float y);

    /**
     * Get the return of this noise function modified by gridPeriod.
     *
     * @param  float x x position in grid to get noise at
     * @param  float y y position in grid to get noise at
     */
    float get(int x, int y);
private:
    static const unsigned int rand_steps = 2048; 

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
