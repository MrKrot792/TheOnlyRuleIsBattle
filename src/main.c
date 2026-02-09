#include <ncurses.h>
#include "world.h"
#include "render.h"
#include "events.h"

void ncursesInit();
void ncursesDeinit();

int main() {
    // Init
    World_init(800, 800);
    ncursesInit();

    // Main loop
    bool running = true;
    while (running) {
        Events_pollEvents();

        erase();
            Render_drawAll();
        refresh();
    }

    // Freeing everything
    ncursesDeinit();
    World_deinit();
    return 0;
}

void ncursesInit() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

void ncursesDeinit() { endwin(); }
