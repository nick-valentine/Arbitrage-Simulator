#include "Services/Logger/BufferLogger.hpp"

BufferLogger::BufferLogger()
{

}

BufferLogger::~BufferLogger()
{

}

void BufferLogger::debug(const char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    this->addToBuffer(Logger::DEBUG, fmt, args);
    va_end(args);
}

void BufferLogger::info(const char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    this->addToBuffer(Logger::INFO, fmt, args);
    va_end(args);
}

void BufferLogger::warn(const char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    this->addToBuffer(Logger::WARN, fmt, args);
    va_end(args);
}

void BufferLogger::error(const char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    this->addToBuffer(Logger::ERROR, fmt, args);
    va_end(args);
    exit(1);
}

void BufferLogger::log(Logger::LogLevel level, const char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    this->addToBuffer(level, fmt, args);
    va_end(args);
}

std::vector<std::string> BufferLogger::getBuffer()
{
    return this->buffer;
}

void BufferLogger::addToBuffer(Logger::LogLevel level, const char *fmt, va_list args)
{
    if (level >= Logger::logLevel) {
        char buffer[256];
        vsnprintf(buffer, 255, fmt, args);
        this->buffer.push_back(buffer);
    }
}
