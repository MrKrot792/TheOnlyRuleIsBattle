#include <string.h>
#include <time.h>

#include "app.h"
#include "world.h"
#include "events.h"
#include "render.h"

static bool running = true;
static int error = APP_OK;
static bool errorMessagePresent = false;
static char errorMessage[2048] = {0};

static float fps = 0.f;

static void App_ncursesInit() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

static void App_ncursesDeinit() { endwin(); }

static double App_now() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

void App_init() {
    World_init(WORLD_WIDTH, WORLD_HEIGHT);
    App_ncursesInit();
}

void App_deinit() {
    World_deinit();
    App_ncursesDeinit();
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

void App_breakWithMessage(int code, const char* message) {
    error = code;
    running = false;
    errorMessagePresent = true;
    strcpy(errorMessage, message);
}

const char* App_errno() {
    if (errorMessagePresent)
        return errorMessage;
    else
        return "No error";
}

bool App_isErrorMessagePresent() { return errorMessagePresent; }
float App_getFps() { return fps; }
