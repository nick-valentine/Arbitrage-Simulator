#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>
#include <curses.h>
#include <vector>

#include "Window/CursesWindow.hpp"

/**
 * GameWindow.
 * Buffer and Curses window for a displaying game world
 */
class GameWindow : public CursesWindow
{
public:
    GameWindow();
    virtual ~GameWindow();

    virtual void init();
    virtual void resize(int height, int width);

    virtual void put(unsigned int colorPair, unsigned int layer, char c, int y, int x);
    virtual void put(Window::TextElement c, int y, int x);

    virtual void clear();

    virtual void render();

private:
    std::vector< std::vector< Window::TextElement > >ScreenBuffer;
};

#endif //SCREEN_HPP
