#include <string.h>
#include <time.h>

#include "app.h"
#include "blocks.h"
#include "layer.h"
#include "world.h"
#include "fps.h"
#include "log.h"

#include "layers/game.h"
#include "layers/exit_button.h"
#include "layers/ui.h"

static bool running = true;
static int error = APP_OK;
static bool error_message_present = false;
static char error_message[2048] = {0};

static FpsInfo fps = {0};

static void App_ncursesInit() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

static void App_ncursesDeinit() { endwin(); }

// TODO: Make this handle time <1sec
static void App_sleepFor(float nanosecs) {
    struct timespec time_to_sleep = { .tv_nsec = nanosecs * 1e9f };
    nanosleep(&time_to_sleep, NULL);
}

void App_init() {
    Blocks_init();
    World_init(WORLD_WIDTH, WORLD_HEIGHT);
    App_ncursesInit();
    Log_init();

    Layer_create(layerExitButton());
    Layer_create(layerUI());
    Layer_create(layerGame());

    Fps_setFramesPerSecond(60);
}

void App_deinit() {
    World_deinit();
    App_ncursesDeinit();
    Log_deinit();
}

int App_loop() {
    while (running) {
        Fps_frameStart();
            Layers_events();
            Layers_update();

            // Not `clear()` because it causes flickering
            erase();
                Layers_render();
            refresh();
        App_sleepFor(Fps_timeToWait(fps));
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
    error_message_present = true;
    strcpy(error_message, message);
}

const char* App_errno() {
    if (error_message_present)
        return error_message;
    else
        return "No error";
}

bool App_isErrorMessagePresent() { return error_message_present; }
FpsInfo App_getFps() { return fps; }
