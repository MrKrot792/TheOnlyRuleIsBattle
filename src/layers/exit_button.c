#include <ncurses.h>
#include "layers/exit_button.h"
#include "app.h"
#include "layer.h"

static bool event(int ch) {
    if (ch == 'q') App_break(APP_OK);
    return false;
}

Layer layerExitButton() {
    return (Layer){
        .init = InitFun_empty(),
        .deinit = SimpleFun_empty(),
        .event = EventFun_make(event),
        .render = SimpleFun_empty(),
        .update = SimpleFun_empty(),
        .ui = SimpleFun_empty(),
    };
}
