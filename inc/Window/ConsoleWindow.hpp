#ifndef CONSOLE_WINDOW_HPP
#define CONSOLE_WINDOW_HPP

#include <curses.h>
#include <list>
#include <string>

#include "ColorPallete.hpp"
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

    static void setPallete();
private:
    static void initColorPallete();

    BufferLogger logger;
    static ColorPallete consolePallete;
    static bool colorPalleteInitialized;

};

#endif //CONSOLE_WINDOW_HPP
