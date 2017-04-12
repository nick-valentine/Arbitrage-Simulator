#ifndef CONSOLE_WINDOW_HPP
#define CONSOLE_WINDOW_HPP

#include <curses.h>
#include <list>
#include <string>

#include "Window/CursesWindow.hpp"
#include "Services/Logger/BufferLogger.hpp"

/**
 * ConsoleWindow.
 * Buffer and Curses window for a displaying in game log 
 */
class ConsoleWindow : public CursesWindow
{
public:
    ConsoleWindow();
    virtual ~ConsoleWindow();

    virtual void render();

    BufferLogger *getLogger();
private:
    BufferLogger logger;

};

#endif //CONSOLE_WINDOW_HPP
