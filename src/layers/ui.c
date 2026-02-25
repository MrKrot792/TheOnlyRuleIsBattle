#include "layers/ui.h"
#include "layers/terminal.h"

#include <ncurses.h>

#include "app.h"
#include "layer.h"
#include "render.h"
#include "character.h"

static uint32_t terminal_id = 0;

static void ui() {
    mvinch(RENDER_REAL_HEIGHT-1, 0);
    clrtoeol();

    FpsInfo fps = App_getFps();
    Character* chr = Character_get();
    Vec2 position = chr->position;
    Render_drawTextAt(Vec2_create(0, RENDER_REAL_HEIGHT - 1),
            "POS: %Gx, %Gy; FPS: %d; Delta: %f; HP: %d; VN: %d; RN: %d;", 

            position.x, position.y,
            fps.fps, fps.delta,
            chr->hp, 
            chr->vultureness,
            chr->ruptureness);
}

static void init() {
    terminal_id = Layer_create(layerTerminal());
}

static void deinit() {
    Layer_destroy(terminal_id);
}

Layer layerUI() {
    return (Layer){
        .render = SimpleFun_empty(),
        .init = InitFun_make(init),
        .deinit = SimpleFun_make(deinit),
        .event = EventFun_empty(),
        .update = SimpleFun_empty(),
        .ui = SimpleFun_make(ui),
    };
}
