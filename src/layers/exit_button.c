#include <ncurses.h>
#include "layers/exit_button.h"
#include "app.h"

static void init() {}
static void deinit() {}
static bool event(int ch) {
    if (ch == 'q') App_break(APP_OK);
    return false;
}
static void render() {}
static void update() {}

Layer layerExitButton() {
    return (Layer){
        .init = init,
        .deinit = deinit,
        .event = event,
        .render = render,
        .update = update,
    };
}
