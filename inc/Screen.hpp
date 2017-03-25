#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>
#include <curses.h>
#include <vector>

/**
 * Screen.
 * Buffer and wrapper for ncurses screen in case this is to be ported to a
 * system where ncurses is unavailable, or a gui is made.
 */
class Screen
{
public:
    struct TextElement {
        unsigned int colorPair;
        unsigned int layer;
        char c;
    };

    Screen();

    void put(unsigned int colorPair, unsigned int layer, char c, int y, int x);
    void put(TextElement c, int y, int x);

    /**
     * Move the internal cursor to x, y
     *
     * @param  int y
     * @param  int x
     * @return bool success
     */
    bool moveTo(int y, int x);
    void clear();

    void render();

    int getHeight();
    int getWidth();
private:
    std::vector< std::vector< TextElement > >ScreenBuffer;
    int width;
    int height;
    int cursor_x;
    int cursor_y;
};

#endif //SCREEN_HPP
