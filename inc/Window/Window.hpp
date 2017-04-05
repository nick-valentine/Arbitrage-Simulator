#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <curses.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

class Window
{
public:
    struct TextElement {
        unsigned int colorPair;
        unsigned int layer;
        char c;
    };

    typedef boost::shared_ptr<Window> window_ptr;
    Window();
    Window(int y, int x, int height, int width);
    virtual ~Window();
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
    static const int borderWidth;
    WINDOW *win; 

    int y;
    int x;
    int height;
    int width;
};

#endif //WINDOW_HPP
