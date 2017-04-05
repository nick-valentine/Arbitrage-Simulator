#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>
#include <curses.h>
#include <vector>

#include "Window/Window.hpp"

/**
 * GameWindow.
 * Buffer and wrapper for ncurses screen in case this is to be ported to a
 * system where ncurses is unavailable, or a gui is made.
 */
class GameWindow : public Window
{
public:
    GameWindow();
    ~GameWindow();

    void init();
    void resize(int height, int width);

    void put(unsigned int colorPair, unsigned int layer, char c, int y, int x);
    void put(Window::TextElement c, int y, int x);

    void clear();

    void render();

private:
    std::vector< std::vector< Window::TextElement > >ScreenBuffer;
};

#endif //SCREEN_HPP
