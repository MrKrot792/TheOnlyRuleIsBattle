#include <string.h>

#include "app.h"
#include "world.h"
#include "events.h"
#include "render.h"
#include "fps.h"
#include "log.h"

static bool running = true;
static int error = APP_OK;
static bool errorMessagePresent = false;
static char errorMessage[2048] = {0};

static FpsInfo fps = {0};

static void App_ncursesInit() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

static void App_ncursesDeinit() { endwin(); }

void App_init() {
    World_init(WORLD_WIDTH, WORLD_HEIGHT);
    App_ncursesInit();
    Log_init();
}

void App_deinit() {
    World_deinit();
    App_ncursesDeinit();
    Log_deinit();
}

int App_loop() {
    while (running) {
        Fps_frameStart();
        Events_pollEvents();

        erase();
            Render_drawAll();
        refresh();
        fps = Fps_frameEnd();
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
FpsInfo App_getFps() { return fps; }
