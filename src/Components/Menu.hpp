#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>
#include <algorithm>

#include "Window/Window.hpp"
#include "Input.hpp"
#include "Context.hpp"

namespace Component
{
    class Menu 
    {
    public:
        Menu();
        Menu(std::string head, std::vector<std::string> options, int top, int left, int height, int width);
        
        void render(Window::window_ptr window);
        int update(Context *ctx);
        void setDims(int top, int left, int height, int width);
    private:
        void drawBorder(Window::window_ptr);
        void drawBar(Window::window_ptr window, int y, int x, int width);
        void drawPipe(Window::window_ptr window, int y, int x, int height);

        std::string head;
        std::vector<std::string> options;
        int top;
        int left;
        int height;
        int width;

        int selected;
    };
}

#endif //MENU_HPP
