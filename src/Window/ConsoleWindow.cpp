#include "Window/ConsoleWindow.hpp"

ColorPallete ConsoleWindow::consolePallete = ColorPallete();
bool ConsoleWindow::colorPalleteInitialized = false;

ConsoleWindow::ConsoleWindow() : CursesWindow()
{
    this->logger.setBufferCapacity(50);
    ConsoleWindow::initColorPallete();
}

ConsoleWindow::~ConsoleWindow()
{

}

void ConsoleWindow::render()
{
    CursesWindow::clear();

    std::list<BufferLogger::LogEntry> &buffer = this->logger.getBuffer();
    int bufferSize = this->logger.getBufferSize();

    int height = this->getHeight();
    int width = this->getWidth();

    int pos_marker = height;

    std::list<BufferLogger::LogEntry>::reverse_iterator rit = buffer.rbegin();
    for (;rit != buffer.rend() && pos_marker > 0; ++rit) {
        pos_marker -= ((*rit).second.size() / width) + 1;
        this->putstr(pos_marker, 1, (*rit).second, (*rit).first);
    }
    CursesWindow::render();
}

BufferLogger *ConsoleWindow::getLogger()
{
    return &this->logger;
}

void ConsoleWindow::setPallete()
{
    ConsoleWindow::consolePallete.setCurrent();
}

void ConsoleWindow::initColorPallete()
{
    if (!ConsoleWindow::colorPalleteInitialized) {
        ConsoleWindow::consolePallete.addColor(COLOR_BLUE, COLOR_BLACK);
        ConsoleWindow::consolePallete.addColor(COLOR_GREEN, COLOR_BLACK);
        ConsoleWindow::consolePallete.addColor(COLOR_YELLOW, COLOR_BLACK);
        ConsoleWindow::consolePallete.addColor(COLOR_RED, COLOR_BLACK);

        ConsoleWindow::colorPalleteInitialized = true;
    }
}
