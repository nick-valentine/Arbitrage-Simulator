#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>
#include <algorithm>

#include "Window/Window.hpp"
#include "Input.hpp"

class Menu 
{
public:
    Menu();
    Menu(std::vector<std::string> options, int top, int left, int height = 0, int width = 0);

    void render(Window::window_ptr window);
    int update(Input input);
private:
    void drawBorder(Window::window_ptr);
    void drawBar(Window::window_ptr window, int y, int x, int width);
    void drawPipe(Window::window_ptr window, int y, int x, int height);

    std::vector<std::string> options;
    int top;
    int left;
    int height;
    int width;

    int selected;
};

#endif //MENU_HPP
