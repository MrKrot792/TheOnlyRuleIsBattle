#include "app.h"
#include "world.h"
#include "events.h"
#include "render.h"

void ncursesInit() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

void ncursesDeinit() { endwin(); }

void App_init() {
    World_init(WORLD_WIDTH, WORLD_HEIGHT);
    ncursesInit();
}

void App_deinit() {
    World_deinit();
    ncursesDeinit();
}

int App_loop() {
    bool running = true;
    while (running) {
        Events_pollEvents();

        erase();
            Render_drawAll();
        refresh();
    }

    return APP_OK;
}
