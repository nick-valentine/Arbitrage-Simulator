#include "Window/GameWindow.hpp"

GameWindow::GameWindow() : Window()
{
}

GameWindow::~GameWindow()
{
}

void GameWindow::init()
{
    this->resize(0, 0);
    Window::init();
}

void GameWindow::resize(int height, int width)
{
    TextElement templ;
    templ.colorPair = 0;
    templ.layer = 0;
    templ.c = ' ';

    ScreenBuffer.clear(); 
    for(int i = 0; i < height - Window::borderWidth; ++i) {
        ScreenBuffer.push_back(std::vector< TextElement >());
        for(int j = 0; j < width - Window::borderWidth; ++j) {
            ScreenBuffer[i].push_back(templ);
        }
    }
    Window::resize(height, width);
}

void GameWindow::put(unsigned int colorPair, unsigned int layer, char c, int y, int x)
{
    TextElement temp;
    temp.colorPair = colorPair;
    temp.layer = layer;
    temp.c = c;
    this->put(temp, y, x);
}

void GameWindow::put(TextElement c, int y, int x)
{
    if(x < width && x > 0 && y < height && y > 0) {
        if(c.layer > ScreenBuffer[y][x].layer) {
            ScreenBuffer[y][x] = c;
        }
    }
}

void GameWindow::clear()
{
    TextElement templ;
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
    attrset(COLOR_PAIR(1));
    wmove(this->win, 1, 1);
    for(int i = 0; i < this->ScreenBuffer.size(); ++i) {
        for(int j = 0; j < this->ScreenBuffer[i].size(); ++j) {
            if(ScreenBuffer[i][j].colorPair != lastColorPair) {
                wattrset(this->win, COLOR_PAIR(ScreenBuffer[i][j].colorPair));
                lastColorPair = ScreenBuffer[i][j].colorPair;
            }
            waddch(this->win, ScreenBuffer[i][j].c);
        }
        wmove(this->win, i, 1);
    }
    Window::render();
}
