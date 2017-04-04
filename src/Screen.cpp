#include "Screen.hpp"

Screen::Screen() : Window()
{
    this->win = 0;
}

Screen::~Screen()
{
    if (this->win != 0) {
        delwin(this->win);
    }
}

void Screen::init()
{

    TextElement templ;
    templ.colorPair = 0;
    templ.layer = 0;
    templ.c = ' ';

    getmaxyx(stdscr, height, width);
    height = height * 0.80; //only allow this screen to take 80% of the viewport
    width-=2;

    for(unsigned int i = 0; i < height; ++i) {
        ScreenBuffer.push_back(std::vector< TextElement >());
        for(unsigned int j = 0; j < width; ++j) {
            ScreenBuffer[i].push_back(templ);
        }
    }

    this->win = newwin(height, width, 1, 1);
    keypad(this->win, TRUE);
    wborder(this->win, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');
    if (this->win == NULL) {
        std::cerr<<"Could not initialize window"<<std::endl;
        exit(1);
    }
    keypad(this->win, TRUE);
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

int Screen::getCh()
{
    return Window::getCh();
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
    unsigned int lastColorPair = 1;
    attrset(COLOR_PAIR(1));
    wmove(win, 0, 0);
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            if(ScreenBuffer[i][j].colorPair != lastColorPair) {
                wattrset(this->win, COLOR_PAIR(ScreenBuffer[i][j].colorPair));
                lastColorPair = ScreenBuffer[i][j].colorPair;
            }
            waddch(this->win, ScreenBuffer[i][j].c);
        }
    }
    Window::render();
}

int Screen::getHeight()
{
    return this->height;
}

int Screen::getWidth()
{
    return this->width;
}

