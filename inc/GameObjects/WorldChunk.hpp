#ifndef WORLDCHUNK_HPP
#define WORLDCHUNK_HPP

#include <sstream>
#include <string>
#include <vector>

#include "Globals.hpp"
#include "GameObjects/AbstractGameObject.hpp"
#include "GameObjects/City.hpp"

class WorldChunk : public AbstractGameObject
{
public:
    WorldChunk();
    WorldChunk(std::istringstream *iss);
    void fromStringStream(std::istringstream *iss);
    void toStringStream(std::ostringstream *oss);

private:
    std::vector<City> cities;
};


#endif //WORLDCHUNK_HPP
