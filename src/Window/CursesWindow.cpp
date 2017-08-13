#include "Window/CursesWindow.hpp"

CursesWindow::CursesWindow()
{
    this->win = NULL;
    this->y = 0;
    this->x = 0;
    this->height = 0;
    this->width = 0;
}

CursesWindow::CursesWindow(int y, int x, int height, int width)
{
    this->win = NULL;
    this->y = y;
    this->x = x;
    this->height = height;
    this->width = width;
}

CursesWindow::~CursesWindow()
{
    if (this->win != NULL) {
        delwin(this->win);
    }
}

void CursesWindow::init()
{
    this->win = newwin(height, width, y, x);
    keypad(this->win, TRUE);
}

void CursesWindow::putstr(int y, int x, std::string str, int color)
{
    wattrset(this->win, COLOR_PAIR(color));
    wmove(this->win, y, x);
    for (int i = 0; i < str.size(); ++i) {
        waddch(this->win, str[i]);
    }
    wattrset(this->win, COLOR_PAIR(0));
}

void CursesWindow::put(unsigned int colorPair, unsigned int layer, char c, int y, int x)
{
    wattrset(this->win, COLOR_PAIR(colorPair));
    wmove(this->win, y, x);
    waddch(this->win, c);
    wattrset(this->win, COLOR_PAIR(0));
}

void CursesWindow::put(TextElement c, int y, int x)
{
    wattrset(this->win, COLOR_PAIR(c.colorPair));
    wmove(this->win, y, x);
    waddch(this->win, c.c);
    wattrset(this->win, COLOR_PAIR(0));
}

void CursesWindow::clear()
{
   werase(this->win); 
}

void CursesWindow::render()
{
    wborder(this->win, 0, 0, 0, 0, 0, 0, 0, 0);
    wrefresh(this->win);
}

void CursesWindow::resize(int height, int width)
{
    this->height = height;
    this->width = width;
    wresize(this->win, height, width);
}

void CursesWindow::move(int y, int x)
{
    this->y = y;
    this->x = x;
    mvwin(this->win, y, x);
}

int CursesWindow::getCh()
{
    wtimeout(this->win, CursesWindow::getchTimeout);
    return wgetch(this->win);
}


int CursesWindow::getY()
{
    return this->y;
}

int CursesWindow::getX()
{
    return this->x;
}

int CursesWindow::getHeight()
{
    return this->height;
}

int CursesWindow::getWidth()
{
    return this->width;
}

