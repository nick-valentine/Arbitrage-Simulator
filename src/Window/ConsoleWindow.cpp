#include "Window/ConsoleWindow.hpp"

ConsoleWindow::ConsoleWindow() : CursesWindow()
{

}

ConsoleWindow::~ConsoleWindow()
{

}

void ConsoleWindow::render()
{
    CursesWindow::clear();
    std::vector<std::string> buffer = this->logger.getBuffer();
    int height = this->getHeight();
    int width = this->getWidth();

    int i = buffer.size() - 1;
    int pos_marker = height;

    while (i >= 0 && pos_marker > 0) {
        pos_marker -= (buffer[i].size() / width) + 1;
        this->putstr(pos_marker, 1, buffer[i]);
        
        --i;
    }
    CursesWindow::render();
}

BufferLogger *ConsoleWindow::getLogger()
{
    return &this->logger;
}
