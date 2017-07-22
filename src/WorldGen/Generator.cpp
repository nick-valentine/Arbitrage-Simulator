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
    for (int i = 0; i < other.passes.size(); ++i) {
        this->passes.push_back(other.passes[i]->clone());
    }
}

Generator *Generator::operator=(const Generator &other)
{
    this->passes = std::vector<AbstractPass*>();
    for (int i = 0; i < other.passes.size(); ++i) {
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

    CityPass *cp = new CityPass();
    cp->init();
    gen.addPass(cp);

    return gen;
}

void Generator::addPass(AbstractPass *pass)
{
    this->passes.push_back(pass);
}

void Generator::execute(World *world, boost::shared_ptr<Logger> logger)
{
    for (int i = 0; i < this->passes.size(); ++i) {
        logger->info("Executing Generator Pass For %s", this->passes[i]->getName().c_str());
        this->passes[i]->execute(world, logger);
    }
    logger->info("Done executing compiler passes");
}
