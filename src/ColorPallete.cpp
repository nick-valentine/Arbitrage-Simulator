#include "ColorPallete.hpp"

ColorPallete::ColorPallete()
{
    this->top = 0;
}

void ColorPallete::addColor(unsigned int fg, unsigned int bg)
{
    this->fg[this->top] = fg;
    this->bg[this->top] = bg;
    top = (top + 1) % ColorPallete::num_colors;
}

void ColorPallete::setCurrent()
{
    if(has_colors() && can_change_color()) {
        for(unsigned int i = 0; i < top; ++i) {
            init_pair(i + 1, fg[i], bg[i]);
        }
    }
}

int ColorPallete::getMaxColor()
{
    return top;
}
