#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>

static void finish(int signal);

static void createWorld(int size_y, int size_x);

int main(int argc, char ** argv)
{
    int max_x;
    int max_y;

    (void) signal(SIGINT, finish);

    (void) initscr();
    (void) getmaxyx(stdscr,max_y,max_x);
    keypad(stdscr, TRUE);
    (void) cbreak();
    (void) noecho();

    if(has_colors()) {
        start_color();
    }

    createWorld(max_y, max_x);

    for(;;) {
        int c = getch();
    }

    finish(0);
}

static void finish(int signal)
{
    (void) nocbreak();
    (void) echo();
    endwin();

    exit(0);
}

static void createWorld(int size_y, int size_x)
{
    srand( time(NULL) );
    static char worldItems[] = {
        '^',
        'M',
        'T',
        '.',
        'W',
        ' '
    };
    move(0,0);
    for(int y = 0; y < size_y; ++y) {
        for(int x = 0; x < size_x; ++x) {
            char c = worldItems[rand() % sizeof(worldItems)];
            addch(c);
        }
        move(y,0);
    }
}
