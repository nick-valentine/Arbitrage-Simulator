#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>

enum Input {
    IGNORED = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SELECT,
    BACK,
    ESCAPE
};

namespace InputMapping 
{
    Input toInput(std::string inputName);
}

#endif //INPUT_HPP
