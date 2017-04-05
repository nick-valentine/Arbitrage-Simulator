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
    void init();

    void putstr(int y, int x, std::string str);
    void render();
    void resize(int height, int width);
    void move(int y, int x);

    int getCh();

    int addSubWindow(int y, int x, int height, int width);
    Window *getSubWindow(int index);

    int getY();
    int getX();
    int getHeight();
    int getWidth();
protected:
    static const int borderWidth;
    WINDOW *win; 

    int y;
    int x;
    int height;
    int width;
};

#endif //WINDOW_HPP
