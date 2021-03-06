#include "Window/GameWindow.hpp"

GameWindow::GameWindow() : CursesWindow()
{
}

GameWindow::~GameWindow()
{
}

void GameWindow::init()
{
    this->resize(0, 0);
    CursesWindow::init();
}

void GameWindow::resize(int height, int width)
{
    Window::TextElement templ;
    templ.colorPair = 0;
    templ.layer = 0;
    templ.c = ' ';

    ScreenBuffer.clear(); 
    for(int i = 0; i < height; ++i) {
        ScreenBuffer.push_back(std::vector< Window::TextElement >());
        for(int j = 0; j < width; ++j) {
            ScreenBuffer[i].push_back(templ);
        }
    }
    CursesWindow::resize(height, width);
}

void GameWindow::putstr(int y, int x, std::string str, int color)
{
    for (int i = 0; i < str.size(); ++i) {
        this->put(color, 999, str[i], y, x + i);
    }
}

void GameWindow::put(unsigned int colorPair, unsigned int layer, char c, int y, int x)
{
    Window::TextElement temp;
    temp.colorPair = colorPair;
    temp.layer = layer;
    temp.c = c;
    this->put(temp, y, x);
}

void GameWindow::put(Window::TextElement c, int y, int x)
{
    if(x < width && x > 0 && y < height && y > 0) {
        if(c.layer > ScreenBuffer[y][x].layer) {
            ScreenBuffer[y][x] = c;
        }
    }
}

void GameWindow::clear()
{
    Window::TextElement templ;
    templ.colorPair = 0;
    templ.layer = 0;
    templ.c = ' ';

    for(unsigned int i = 0; i < this->ScreenBuffer.size(); ++i) {
        for(unsigned int j = 0; j < this->ScreenBuffer[i].size(); ++j) {
            ScreenBuffer[i][j] = templ;
        }
    }

}

void GameWindow::render()
{
    unsigned int lastColorPair = 1;
    wattrset(this->win, COLOR_PAIR(1));
    wmove(this->win, 0, 0);
    for(int i = 0; i < this->ScreenBuffer.size(); ++i) {
        for(int j = 0; j < this->ScreenBuffer[i].size(); ++j) {
            if(ScreenBuffer[i][j].colorPair != lastColorPair) {
                wattrset(this->win, COLOR_PAIR(ScreenBuffer[i][j].colorPair));
                lastColorPair = ScreenBuffer[i][j].colorPair;
            }
            waddch(this->win, ScreenBuffer[i][j].c);
        }
        wmove(this->win, i, 0);
    }
    CursesWindow::render();
}

