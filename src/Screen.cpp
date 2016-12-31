#include "Screen.hpp"

Screen::Screen()
{
    this->cursor_x = 0;
    this->cursor_y = 0;
    getmaxyx(stdscr, height, width);

    TextElement templ;
    templ.colorPair = 0;
    templ.layer = 0;
    templ.c = ' ';
    std::cout<<height<<width<<std::endl;

    for(unsigned int i = 0; i < height; ++i) {
        ScreenBuffer.push_back(std::vector< TextElement >());
        for(unsigned int j = 0; j < width; ++j) {
            ScreenBuffer[i].push_back(templ);
        }
    }
}

void Screen::put(unsigned int colorPair, unsigned int layer, char c, int y, int x)
{
    TextElement temp;
    temp.colorPair = colorPair;
    temp.layer = layer;
    temp.c = c;
    this->put(temp, y, x);
}

void Screen::put(TextElement c, int y, int x)
{
    if(x < width && x > 0 && y < height && y > 0) {
        if(c.layer > ScreenBuffer[y][x].layer) {
            ScreenBuffer[y][x] = c;
        }
    }
}

bool Screen::moveTo(int y, int x)
{
    if(y < height && y > 0 && 
        x < width && x > 0) { 
        this->cursor_y = y;
        this->cursor_x = x;
        return true;
    }
    return false;
}

void Screen::clear()
{
    TextElement templ;
    templ.colorPair = 0;
    templ.layer = 0;
    templ.c = ' ';

    for(unsigned int i = 0; i < height; ++i) {
        for(unsigned int j = 0; j < width; ++j) {
            ScreenBuffer[i][j] = templ;
        }
    }

}

void Screen::render()
{
    unsigned int lastColorPair = 0;
    attrset(COLOR_PAIR(0));
    move(0, 0);
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            if(ScreenBuffer[i][j].colorPair != lastColorPair) {
                attrset(COLOR_PAIR(ScreenBuffer[i][j].colorPair));
                lastColorPair = ScreenBuffer[i][j].colorPair;
            }
            addch(ScreenBuffer[i][j].c);
        }
    }
}
