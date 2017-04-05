#include "Window/Window.hpp"

const int Window::borderWidth = 2;

Window::Window()
{
    this->win = NULL;
    this->y = 0;
    this->x = 0;
    this->height = 0;
    this->width = 0;
}

Window::Window(int y, int x, int height, int width)
{
    this->win = NULL;
    this->y = y;
    this->x = x;
    this->height = height;
    this->width = width;
}

Window::~Window()
{
    if (this->win != NULL) {
        delwin(this->win);
    }
}

void Window::init()
{
    this->win = newwin(height, width, y, x);
    keypad(this->win, TRUE);
    wborder(this->win, '|', '|', '-', '-', '+', '+', '+', '+');
}

void Window::putstr(int y, int x, std::string str)
{
    wmove(this->win, y, x);
    for (int i = 0; i < str.size(); ++i) {
        waddch(this->win, str[i]);
    }
}

void Window::render()
{
    wrefresh(this->win);
}

void Window::resize(int height, int width)
{
    this->height = height;
    this->width = width;
    wresize(this->win, height, width);
}

void Window::move(int y, int x)
{
    this->y = y;
    this->x = x;
    mvwin(this->win, y, x);
}

int Window::getCh()
{
    return wgetch(this->win);
}


int Window::getY()
{
    return this->y;
}

int Window::getX()
{
    return this->x;
}

int Window::getHeight()
{
    return this->height;
}

int Window::getWidth()
{
    return this->width;
}

