#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <curses.h>
#include <string>
#include <vector>

class Window
{
public:
    Window();
    Window(int y, int x, int height, int width);
    ~Window();

    void putstr(int y, int x, std::string str);
    void render();

    int getCh();

    int addSubWindow(int y, int x, int height, int width);
    Window *getSubWindow(int index);
protected:
    WINDOW *win; 
};

#endif //WINDOW_HPP
