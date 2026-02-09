#include <ncurses.h>
#include "world.h"
#include "render.h"

int main() {
    // Init
    World_init(800, 800);
    initscr();

    bool running = true;
    while (running) {
        Render_drawAll();
        refresh();
        getch();
    }

    // Freeing everything
    endwin();
    World_deinit();
    return 0;
}
