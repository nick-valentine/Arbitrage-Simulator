#ifndef CURSES_WINDOW_HPP
#define CURSES_WINDOW_HPP

#include <iostream>
#include <curses.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "Window/Window.hpp"

/**
 * CursesWindow.
 * Buffer and wrapper for ncurses screen in case this is to be ported to a
 * system where ncurses is unavailable, or a gui is made.
 */
class CursesWindow : public Window
{
public:
    typedef boost::shared_ptr<Window> window_ptr;
    CursesWindow();
    CursesWindow(int y, int x, int height, int width);
    virtual ~CursesWindow();
    virtual void init();

    virtual void putstr(int y, int x, std::string str);
    virtual void put(unsigned int colorPair, unsigned int layer, char c, int y, int x);
    virtual void put(TextElement c, int y, int x);
    virtual void clear();

    virtual void render();
    virtual void resize(int height, int width);
    virtual void move(int y, int x);

    virtual int getCh();

    virtual int getY();
    virtual int getX();
    virtual int getHeight();
    virtual int getWidth();
protected:
    WINDOW *win; 

    int y;
    int x;
    int height;
    int width;
};

#endif //CURSES_WINDOW_HPP

