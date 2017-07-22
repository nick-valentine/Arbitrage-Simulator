#include "WorldGen/Generator.hpp"

Generator::Generator()
{
    this->passes = std::vector<AbstractPass*>();
}

Generator::~Generator()
{
    for (int i = 0; i < this->passes.size(); ++i) {
        delete this->passes[i];
    }
}

Generator::Generator(const Generator &other)
{
    this->passes = std::vector<AbstractPass*>();
    for (int i = 0; i < this->passes.size(); ++i) {
        this->passes.push_back(other.passes[i]->clone());
    }
}

Generator *Generator::operator=(const Generator &other)
{
    this->passes = std::vector<AbstractPass*>();
    for (int i = 0; i < this->passes.size(); ++i) {
        this->passes.push_back(other.passes[i]->clone());
    }
}

Generator Generator::DefaultGenerator()
{
    Generator gen;

    ElevationPass *ep = new ElevationPass();
    ep->init();
    gen.addPass(ep);

    TypePass *tp = new TypePass();
    tp->init();
    gen.addPass(tp);

    return gen;
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
