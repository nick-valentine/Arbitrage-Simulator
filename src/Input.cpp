#include "Input.hpp"

Input InputMapping::toInput(std::string inputName)
{
    if (inputName == "up") {
        return Input::UP;
    }

    if (inputName == "down") {
        return Input::DOWN;
    }

    if (inputName == "left") {
        return Input::LEFT;
    }

    if (inputName == "right") {
        return Input::RIGHT;
    }

    if (inputName == "select") {
        return Input::SELECT;
    }

    if (inputName == "back") {
        return Input::BACK;
    }

    return Input::IGNORED;
}
