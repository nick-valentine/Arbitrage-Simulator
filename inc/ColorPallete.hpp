#ifndef COLORPALLETE_HPP
#define COLORPALLETE_HPP

#include <curses.h>

class ColorPallete 
{
public:
    ColorPallete();
    void addColor(unsigned int fg, unsigned int bg);
    void setCurrent();

    int getMaxColor();
private: 
    static const unsigned int num_colors = 8;

    unsigned int top;
    unsigned int fg[num_colors];
    unsigned int bg[num_colors];
};

#endif //COLORPALLETE_HPP
