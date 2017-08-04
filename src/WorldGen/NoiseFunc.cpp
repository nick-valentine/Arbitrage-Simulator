#include "WorldGen/NoiseFunc.hpp"

NoiseFunc::NoiseFunc()
{
    srand( time( NULL) );
    Grid = std::vector< std::vector< std::pair< float, float > > >();
    Grid.push_back(std::vector< std::pair< float, float > >());
    Grid[0].push_back(this->newRandPair());

    this->gridPeriod = 1.0;
}

NoiseFunc::NoiseFunc(float gridPeriod)
{
    Grid = std::vector< std::vector< std::pair< float, float > > >();
    Grid.push_back(std::vector< std::pair< float, float > >());
    Grid[0].push_back(this->newRandPair());

    this->gridPeriod = gridPeriod;
}

NoiseFunc::NoiseFunc(std::stringstream *ss)
{   
    this->fromStringStream(ss); 
}

void NoiseFunc::fromStringStream(std::stringstream *ss)
{
    float x, y;
    int size_x, size_y;
    (*ss)>>size_x>>size_y>>this->gridPeriod;
    for(int i = 0; i < size_y; ++i) {
            this->Grid.push_back(std::vector< std::pair<float, float> >());
        for(int j = 0; j < size_x; ++j) {
            (*ss)>>x>>y;
            this->Grid[i].push_back(std::pair<float, float>(x, y));
        }
    }
}

void NoiseFunc::toStringStream(std::stringstream *ss)
{
    int size_y = this->Grid.size();
    int size_x = (size_y > 0) ? this->Grid[0].size() : 0;
    (*ss)<<" "<<size_x<<" "<<size_y<<" "<<this->gridPeriod<<" ";
    for(int i = 0; i < size_y; ++i) {
        for(int j = 0; j < size_x; ++j) {
            float x = this->Grid[i][j].first;
            float y = this->Grid[i][j].second;
            (*ss)<<x<<" "<<y<<" ";
        }
    }
}

float NoiseFunc::getRaw(float x, float y)
{
    return this->perlin(x, y);
}

float NoiseFunc::get(int x, int y)
{
    return this->perlin(x / this->gridPeriod, y / this->gridPeriod);
}

float NoiseFunc::perlin(float x, float y)
{
    //determine grid cell coordinates
    //int x0 = (x > 0.0f ? (int)x : (int)x - 1);
    int x0 = (int)x;
    int x1 = x0 + 1;
    //int y0 = (y > 0.0f ? (int)y : (int)y - 1);
    int y0 = (int)y;
    int y1 = y0 + 1;

    //interpolation weights
    float sx = x - (float)x0;
    float sy = y - (float)y0;

    //interpolate between grid point gradients
    float n0, n1, ix0, ix1, value;
    n0 = this->dotGridGradient(x0, y0, x, y);
    n1 = this->dotGridGradient(x1, y0, x, y);
    ix0 = this->lerp(n0, n1, sx);
    n0 = this->dotGridGradient(x0, y1, x, y);
    n1 = this->dotGridGradient(x1, y1, x, y);
    ix1 = this->lerp(n0, n1, sx);
    return lerp(ix0, ix1, sy);
}

float NoiseFunc::dotGridGradient(int ix, int iy, float x, float y)
{
    this->addGridGradient(ix, iy);

    float dx = x - (float)ix;
    float dy = y - (float)iy;

    return (dx * this->Grid[iy][ix].first) + (dy * Grid[iy][ix].second);
}

float NoiseFunc::lerp(float a0, float a1, float w)
{
    return ( (1.0f - w) * a0 ) + (w * a1);
}

void NoiseFunc::addGridGradient(int x, int y)
{
    int size_y = this->Grid.size();
    int size_x = (size_y > 0) ? this->Grid[0].size() : 0;
    int dy = (y+1) - size_y; 
    int dx = (x+1) - size_x; 

    for(int i = 0; i < dy; ++i) {
        this->Grid.push_back(std::vector< std::pair< float, float > >());
        int fillY = this->Grid.size() - 1;
        for(int j = 0; j < Grid[0].size(); ++j) {
            this->Grid[fillY].push_back(this->newRandPair());
        }
    }

    for(int i = 0; i < dx; ++i) {
        for(int j = 0; j < this->Grid.size(); ++j) {
            this->Grid[j].push_back(newRandPair());
        }
    }
}

float NoiseFunc::newRand()
{
    return (rand() % NoiseFunc::rand_steps) / (float)NoiseFunc::rand_steps;
}

std::pair<float, float> NoiseFunc::newRandPair()
{
    return std::pair<float, float>(newRand(), newRand());
}

