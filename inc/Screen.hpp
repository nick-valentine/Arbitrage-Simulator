#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>
#include <curses.h>
#include <vector>

#include "Window.hpp"

/**
 * Screen.
 * Buffer and wrapper for ncurses screen in case this is to be ported to a
 * system where ncurses is unavailable, or a gui is made.
 */
class Screen : private Window
{
public:
    struct TextElement {
        unsigned int colorPair;
        unsigned int layer;
        char c;
    };

    Screen();
    ~Screen();

    void init();

    void put(unsigned int colorPair, unsigned int layer, char c, int y, int x);
    void put(TextElement c, int y, int x);
    int getCh();

    void clear();

    void render();

    int getHeight();
    int getWidth();

private:
    std::vector< std::vector< TextElement > >ScreenBuffer;
    int width;
    int height;
};

#endif //SCREEN_HPP
