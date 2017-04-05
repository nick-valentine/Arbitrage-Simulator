#ifndef GAME_WINDOW_LAYOUT_HPP
#define GAME_WINDOW_LAYOUT_HPP

#include <iostream>
#include <stdlib.h>
#include <map>
#include <string>
#include <curses.h>
#include <algorithm>

#include "Window/Window.hpp"

class GameWindowLayout
{
public:
    GameWindowLayout();
    ~GameWindowLayout();

    void addWindow(std::string name, Window::window_ptr window);
    void delWindow(std::string name);

    void setMainWindow(std::string name);
    void setSubWindow(std::string name);

    void setSubWindowMinHeight(int height);

    void render();
    void updateScreenSize(bool force = false);
private:
    const static float screenRatioForMainWindow;

    Window::window_ptr mainWindow;
    Window::window_ptr subWindow;
    std::map<std::string, Window::window_ptr> windows;

    int windowHeight;
    int windowWidth;

    int subWindowMinHeight;
};

#endif //GAME_WINDOW_LAYOUT_HPP
