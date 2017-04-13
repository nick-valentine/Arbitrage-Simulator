#include "Services/Logger/Logger.hpp"

const std::string Logger::levelStrings[4] = {
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR" 
};

int Logger::logLevel = 0;

void Logger::configure()
{
    //do not let Errors be suppressed
    Logger::logLevel = std::max(
        ConfigLoader::getIntOption("log_level", 0),
        int(WARN)
    ); 
}

std::string Logger::format_string(LogLevel level, const char *fmt, va_list args)
{
    char b[256];
    vsnprintf(b, 255, fmt, args);

    std::string formatted = "[" + 
        Logger::levelStrings[level] + 
        ": " + 
        this->get_time() + 
        "] "
    ;
    formatted += b;
    return formatted;
}

std::string Logger::get_time()
{
    char buffer[80];
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
    std::string time = buffer;
    return time;
}
