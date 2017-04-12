#include "Services/Logger/BufferLogger.hpp"

const int BufferLogger::defaultCapacity = 50;

BufferLogger::BufferLogger()
{
    this->buffer = std::list<std::string>();
    this->bufferCapacity = BufferLogger::defaultCapacity;
}

BufferLogger::~BufferLogger()
{

}

void BufferLogger::setBufferCapacity(int newCapacity)
{
    this->bufferCapacity = newCapacity;
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

std::list<std::string> &BufferLogger::getBuffer() 
{
    return this->buffer;
}

int BufferLogger::getBufferSize()
{
    return this->bufferSize;
}

void BufferLogger::addToBuffer(Logger::LogLevel level, const char *fmt, va_list args)
{
    if (level <= Logger::logLevel) {
        char b[256];
        vsnprintf(b, 255, fmt, args);
        this->buffer.push_back(b);
        this->bufferSize++;
        while (this->bufferSize > this->bufferCapacity) {
            this->buffer.pop_front();
            this->bufferSize--;
        }
    }
}
