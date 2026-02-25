#include "layers/terminal.h"
#include "layer.h"
#include "log.h"
#include "render.h"
#include "vec2.h"

static void ui() {
    Render_drawTextAt((Vec2){0, 0}, "Logs:");
    int at = lastLog.tail;
    int position = 0;

    do {
        Render_drawTextAt((Vec2){0, position+1}, "  %s", lastLog.memory[at]);

        if ((at + 1) == LOG_LOG_UI_SIZE) at = 0;
        else at++;
        position++;
    } while (at != lastLog.tail);
}

static bool event(int ch) {
    if (ch == 'j') Log(LOG_WARNING, "IDK BRUH!!: %s", "i don't know");
    if (ch == 'k') Log(LOG_WARNING, "dkad");
    if (ch == 'l') Log(LOG_WARNING, "l");
    return false;
}

Layer layerTerminal() {
    return (Layer){
        .init = InitFun_empty(),
        .deinit = SimpleFun_empty(),
        .event = EventFun_make(event),
        .render = SimpleFun_empty(),
        .ui = SimpleFun_make(ui),
        .update = SimpleFun_empty(),
    };
}
