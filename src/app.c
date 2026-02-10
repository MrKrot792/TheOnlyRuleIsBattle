#include <time.h>

#include "app.h"
#include "world.h"
#include "events.h"
#include "render.h"

bool running = true;
int error = APP_OK;

float fps = 0.f;

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

double App_now() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int App_loop() {
    double last = App_now();

    while (running) {
        // FPS stuff
        double current = App_now();
        double delta = current - last;
        fps = 1.0 / delta;

        Events_pollEvents();

        erase();
            Render_drawAll();
        refresh();
        last = current;
    }

    return error;
}

void App_break(int code) {
    error = code;
    running = false;
}

float App_getFps() {
    return fps;
}
