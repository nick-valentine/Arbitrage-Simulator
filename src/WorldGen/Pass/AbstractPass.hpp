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
    virtual void execute(World *world) = 0;
protected:
    std::vector< std::vector<WorldChunk> > getChunks(World *world);
    void setChunks(World *world, std::vector< std::vector<WorldChunk> > chunks);

    unsigned int getWorldHeight();
    unsigned int getWorldWidth();
    int getChunkHeight(World *world);
    int getChunkWidth(World *world);
private:

};

#endif //ABSTRACT_PASS_HPP
