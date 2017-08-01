#ifndef NULL_LOGGER_HPP
#define NULL_LOGGER_HPP

class NullLogger : public Logger
{
public:
    virtual void debug(const char *fmt, ...){};
    virtual void info(const char *fmt, ...){};
    virtual void warn(const char *fmt, ...){};
    virtual void error(const char *fmt, ...){};
    virtual void log(Logger::LogLevel level, const char *fmt, ...){};
private:
};

#endif //NULL_LOGGER_HPP
