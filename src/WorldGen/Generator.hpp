#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <vector>

#include "GameObjects/World.hpp"
#include "WorldGen/Pass/AbstractPass.hpp"

class Generator
{
public:
    Generator();

    void addPass(AbstractPass *pass);

    void execute(World *world);
private:
    std::vector<AbstractPass*> passes;
};

#endif //GENERATOR_HPP
