#ifndef CONSOLE_LOGGER_HPP
#define CONSOLE_LOGGER_HPP

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "Services/Logger/Logger.hpp"

class ConsoleLogger : public Logger
{
public:
    ConsoleLogger();
    virtual ~ConsoleLogger();
    virtual void debug(const char *fmt, ...);
    virtual void info(const char *fmt, ...);
    virtual void warn(const char *fmt, ...);
    virtual void error(const char *fmt, ...);
    virtual void log(Logger::LogLevel level, const char *fmt, ...);
protected:
    virtual void print(Logger::LogLevel level, const char *fmt, va_list args); 
};

#endif //CONSOLE_LOGGER_HPP
