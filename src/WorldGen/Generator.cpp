#include "WorldGen/Generator.hpp"

Generator::Generator()
{
    this->passes = std::vector<AbstractPass*>();
}

void Generator::addPass(AbstractPass *pass)
{
    this->passes.push_back(pass);
}

void Generator::execute(World *world)
{
    for (int i = 0; i < this->passes.size(); ++i) {
        this->passes[i]->execute(world);
    }
}
