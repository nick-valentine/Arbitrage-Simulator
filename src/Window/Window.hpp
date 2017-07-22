#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

/**
 * Window.
 * Interface for all windows to follow.
 */
class Window
{
public:
    struct TextElement {
        unsigned int colorPair;
        unsigned int layer;
        char c;
    };

    typedef boost::shared_ptr<Window> window_ptr;
    virtual ~Window() {};
    virtual void init() = 0;

    virtual void putstr(int y, int x, std::string str, int color = 0) = 0;
    virtual void put(unsigned int colorPair, unsigned int layer, char c, int y, int x) = 0;
    virtual void put(TextElement c, int y, int x) = 0;
    virtual void clear() = 0;

    virtual void render() = 0;
    virtual void resize(int height, int width) = 0;
    virtual void move(int y, int x) = 0;

    virtual int getCh() = 0;

    virtual int getY() = 0;
    virtual int getX() = 0;
    virtual int getHeight() = 0;
    virtual int getWidth() = 0;
};

#endif //WINDOW_HPP
