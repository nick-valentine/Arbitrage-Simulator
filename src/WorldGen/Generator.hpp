#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <vector>

#include "GameObjects/World.hpp"
#include "WorldGen/Pass/AbstractPass.hpp"

#include "WorldGen/Pass/ElevationPass.hpp"
#include "WorldGen/Pass/TypePass.hpp"

class Generator
{
public:
    Generator();
    ~Generator();
    Generator(const Generator &other);
    Generator *operator=(const Generator &other);

    static Generator DefaultGenerator();

    void addPass(AbstractPass *pass);

    void execute(World *world);
private:
    std::vector<AbstractPass*> passes;
};

#endif //GENERATOR_HPP
