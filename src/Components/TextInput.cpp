#include "Components/TextInput.hpp"

Component::TextInput::TextInput()
{
    this->label = "";
    this->top = -1;
    this->left = -1;
    this->isDone = false;
    this->input = "";
}

Component::TextInput::TextInput(std::string label, int top, int left)
{
    this->label = label;
    this->top = top;
    this->left = left;
    this->isDone = false;
    this->input = "";
}

void Component::TextInput::render(Window::window_ptr window)
{
    window->putstr(this->top, this->left, this->label, 0);
    window->putstr(this->top, this->left + this->label.size(), this->input, 0);
}

std::string Component::TextInput::update(Context *ctx)
{
    int input = ctx->rawInput;
    if (input >= 32 && input <= 126) {
        this->input  += char(input);
    }
    if (ctx->input == Input::ESCAPE) {
        this->isDone = true;
    }
    return this->input;
}

bool Component::TextInput::done()
{
    return this->isDone;
}


