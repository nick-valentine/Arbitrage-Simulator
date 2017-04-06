#ifndef BUFFER_LOGGER_HPP
#define BUFFER_LOGGER_HPP

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

#include "Services/Logger/Logger.hpp"

/**
 * BufferLogger.
 * Log direcly to a vector of strings.
 * Utility class for things like a console window.
 */
class BufferLogger : public Logger
{
public:
    BufferLogger();
    virtual ~BufferLogger();
    virtual void debug(const char *fmt, ...);
    virtual void info(const char *fmt, ...);
    virtual void warn(const char *fmt, ...);
    virtual void error(const char *fmt, ...);
    virtual void log(Logger::LogLevel level, const char *fmt, ...);

    virtual std::vector<std::string> getBuffer();
protected:
    virtual void addToBuffer(Logger::LogLevel level, const char *fmt, va_list args); 

    std::vector<std::string> buffer;
};

#endif //BUFFER_LOGGER_HPP
