#ifndef ABSTRACT_PASS_HPP
#define ABSTRACT_PASS_HPP

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

#include "GameObjects/World.hpp"
#include "GameObjects/WorldChunk.hpp"

#include "Services/Logger/Logger.hpp"

/**
 * Abstract world pass.
 * A root interface for all world generation passes to follow.
 */
class AbstractPass 
{
public:
    virtual void init(){};
    virtual void execute(World *world, boost::shared_ptr<Logger> logger);

    virtual AbstractPass *clone() = 0;
    virtual std::string getName() = 0;
protected:
    virtual void executeChunk(int top, int left, WorldChunk *chunk);
    virtual void doTile(int i, int j, Tile *tile, WorldChunk *chunk) = 0;
};

#endif //ABSTRACT_PASS_HPP
