#include "app.h"
#include "world.h"
#include "events.h"
#include "render.h"

bool running = true;
int error = APP_OK;

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
    while (running) {
        Events_pollEvents();

        erase();
            Render_drawAll();
        refresh();
    }

    return error;
}

void App_break(int code) {
    error = code;
    running = false;
}
