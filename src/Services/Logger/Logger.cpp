#include "Services/Logger/Logger.hpp"

int Logger::logLevel = 0;

void Logger::configure()
{
    //do not let Errors be suppressed
    Logger::logLevel = std::max(
        ConfigLoader::getIntOption("log_level", 0),
        int(WARN)
    ); 
}
