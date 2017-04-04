#include "Window.hpp"

Window::Window()
{
    this->win = NULL;
}

Window::Window(int y, int x, int height, int width)
{
    this->win = newwin(height, width, y, x);
    keypad(this->win, TRUE);
    wborder(this->win, '|', '|', '-', '-', '+', '+', '+', '+');
}

Window::~Window()
{
    delwin(this->win);
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

int Window::getCh()
{
    return wgetch(this->win);
}

