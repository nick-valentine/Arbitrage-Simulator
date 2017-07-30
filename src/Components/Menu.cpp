#include "Components/Menu.hpp"

Menu::Menu()
{
    this->options = std::vector<std::string>();
    this->top = 0;
    this->left = 0;
    this->height = 0;
    this->width = 0;
    this->selected = 0;
}

Menu::Menu(std::vector<std::string> options, int top, int left, int height, int width)
{
    this->options = options;
    this->top = top;
    this->left = left;
    this->height = height;
    this->width = width;
    this->selected = 0;
}

void Menu::render(Window::window_ptr window)
{
    this->drawBorder(window);

    int maxHeight = std::min(this->height, int(this->options.size()));
    for (int i = 0; i < maxHeight; ++i) {
        int color = this->selected == i ? 1 : 0;
        window->putstr(this->top + i + 1, this->left + 1, this->options[i], color);
    }

}

int Menu::update(Input input)
{
    switch (input) {
        case Input::UP:
            this->selected = std::max(this->selected - 1, 0);
            return -1;
        case Input::DOWN:
            this->selected = std::min(this->selected + 1, int(this->options.size() - 1));
            return -1;
        case Input::SELECT:
            return selected;
        case Input::BACK:
            return -2;
    };
}

void Menu::drawBorder(Window::window_ptr window)
{
    this->drawBar(window, this->top, this->left, this->width);
    this->drawBar(window, this->top + this->height, this->left, this->width);
    this->drawPipe(window, this->top, this->left, this->height);
    this->drawPipe(window, this->top, this->left + this->width, this->height);
}

void Menu::drawBar(Window::window_ptr window, int y, int x, int width)
{
    for (int i = 0; i < width; ++i) {
        window->put(0, 999, '-', y, i + x);
    }
}

void Menu::drawPipe(Window::window_ptr window, int y, int x, int height)
{
    for (int i = 0; i < height; ++i) {
        window->put(0, 999, '|', i + y, x);
    }
}
