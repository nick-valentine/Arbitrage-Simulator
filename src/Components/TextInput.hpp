#ifndef TEXTINPUT_HPP
#define TEXTINPUT_HPP

#include <string>

#include "Window/Window.hpp"
#include "Context.hpp"

namespace Component
{
    class TextInput
    {
    public:
        TextInput();
        TextInput(std::string label, int top, int left);

        void render(Window::window_ptr window);
        std::string update(Context *ctx);
        bool done();
    private:
        int top;
        int left;
        std::string label;
        std::string input;
        bool isDone;
    };
}

#endif //TEXTINPUT_HPP
