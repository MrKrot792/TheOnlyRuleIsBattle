#include <ncurses.h>
#include "world.h"

int main() {
    World_init(800, 800);
    initscr();
    printw("Yo");
    refresh();
    getch();
    endwin();
    World_deinit();
    return 0;
}
