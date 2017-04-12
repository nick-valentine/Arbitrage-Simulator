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
    std::list<std::string> &buffer = this->logger.getBuffer();
    int bufferSize = this->logger.getBufferSize();

    int height = this->getHeight();
    int width = this->getWidth();

    int pos_marker = height;

    std::list<std::string>::reverse_iterator rit = buffer.rbegin();
    for (;rit != buffer.rend() && pos_marker > 0; ++rit) {
        pos_marker -= ((*rit).size() / width) + 1;
        this->putstr(pos_marker, 1, (*rit));
    }
    CursesWindow::render();
}

BufferLogger *ConsoleWindow::getLogger()
{
    return &this->logger;
}
