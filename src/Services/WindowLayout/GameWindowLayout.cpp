#include "Services/WindowLayout/GameWindowLayout.hpp"

const float GameWindowLayout::screenRatioForMainWindow = 0.80;

GameWindowLayout::GameWindowLayout()
{
}

GameWindowLayout::~GameWindowLayout()
{
}

void GameWindowLayout::addWindow(std::string name, Window::window_ptr window)
{
    if (this->windows.find(name) == this->windows.end()) {
        this->windows[name] = window;
    } else {
        std::cout<<"Error, Window Layout Can Not Have Two Windows With The Same Name"<<std::endl;
        exit(EXIT_FAILURE);
    }
}

void GameWindowLayout::delWindow(std::string name)
{
    if (this->windows.find(name) != this->windows.end()) {
        this->windows.erase(name);
    } else {
        std::cout<<"Error, Window Layout Can Not Delete Window That Does Not Exist"<<std::endl;
        exit(EXIT_FAILURE);
    }
}

void GameWindowLayout::setMainWindow(std::string name)
{
    if (this->windows.find(name) != this->windows.end()) {
            this->mainWindow = this->windows[name];
            this->updateScreenSize(true);
    } else {
        std::cout<<"Error, Window Layout Can Set Main Window To One That Does Not Exist"<<std::endl;
        exit(EXIT_FAILURE);
    }
}

void GameWindowLayout::setSubWindow(std::string name)
{
    if (this->windows.find(name) != this->windows.end()) {
            this->subWindow = this->windows[name];
            this->updateScreenSize(true);
    } else {
        std::cout<<"Error, Window Layout Can Set Sub Window To One That Does Not Exist"<<std::endl;
        exit(EXIT_FAILURE);
    }
}

void GameWindowLayout::setSubWindowMinHeight(int height)
{
    this->subWindowMinHeight = height;
    this->updateScreenSize(true);
}

void GameWindowLayout::render()
{
    this->updateScreenSize();
    wborder(stdscr, 0, 0, 0, 0, 0, 0, 0, 0);
    this->mainWindow->render();
    this->subWindow->render();
}

void GameWindowLayout::updateScreenSize(bool force)
{
    int newHeight, newWidth;
    getmaxyx(stdscr, newHeight, newWidth);
    if (
        force ||
        newHeight != this->windowHeight ||
        newWidth != this->windowWidth
    ) {
        this->windowHeight = newHeight;
        this->windowWidth = newWidth;

        int windowWidths = this->windowWidth - 2;
        int subWindowHeight = std::max(
            int(this->windowHeight * (1.0 - GameWindowLayout::screenRatioForMainWindow)) - 1,
            int(this->subWindowMinHeight)
        );
        int mainWindowHeight = this->windowHeight - subWindowHeight - 1;

        if (this->mainWindow != NULL) {
            this->mainWindow->resize(mainWindowHeight, windowWidths);
            this->mainWindow->move(1, 1);
        }
        if (this->subWindow != NULL) {
            this->subWindow->resize(subWindowHeight, windowWidths);
            this->subWindow->move(mainWindowHeight, 1);
        }
    }
}
