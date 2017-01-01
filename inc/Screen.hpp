#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>
#include <curses.h>
#include <vector>

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
