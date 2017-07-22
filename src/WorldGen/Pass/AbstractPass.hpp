#ifndef ABSTRACT_PASS_HPP
#define ABSTRACT_PASS_HPP

#include <vector>

#include "GameObjects/World.hpp"
#include "GameObjects/WorldChunk.hpp"

/**
 * Abstract world pass.
 * A root interface for all world generation passes to follow.
 */
class AbstractPass 
{
public:
    virtual void init(){};
    virtual void execute(World *world);
protected:
    virtual void executeChunk(int top, int left, WorldChunk *chunk);
    virtual void doTile(int i, int j, Tile *tile) = 0;
};

#endif //ABSTRACT_PASS_HPP
