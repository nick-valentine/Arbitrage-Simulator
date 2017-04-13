#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <stdarg.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <ctime>

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
    const static std::string levelStrings[4];
    static int logLevel;

    virtual std::string format_string(LogLevel level, const char *fmt, va_list args);
    std::string get_time();
};

#endif //LOGGER_HPP
