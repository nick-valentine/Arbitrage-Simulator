#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <stdarg.h>
#include <stdio.h>
#include <algorithm>

#include "ConfigLoader.hpp"

class Logger
{
public:
    enum LogLevel {
        NONE = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4
    };


    virtual ~Logger(){};
    virtual void debug(const char *fmt, ...) = 0;
    virtual void info(const char *fmt, ...) = 0;
    virtual void warn(const char *fmt, ...) = 0;
    virtual void error(const char *fmt, ...) = 0;
    virtual void log(Logger::LogLevel level, const char *fmt, ...) = 0;

    static void configure();
protected:
    static int logLevel;
};

#endif //LOGGER_HPP
