#include "layers/ui.h"

#include <ncurses.h>

#include "app.h"
#include "layer.h"
#include "render.h"
#include "character.h"

static void ui() {
    mvinch(RENDER_REAL_HEIGHT-1, 0);
    clrtoeol();

    FpsInfo fps = App_getFps();
    Vec2 position = Character_getPosition();
    Render_drawTextAt(Vec2_create(0, RENDER_REAL_HEIGHT - 1),
            "HP: %d; POS: %Gx, %Gy; FPS: %d; Delta: %f;", 

            Character_getHp(), 
            position.x, position.y,
            fps.fps, fps.delta);
}

Layer layerUI() {
    return (Layer){
        .render = SimpleFun_empty(),
        .init = InitFun_empty(),
        .deinit = SimpleFun_empty(),
        .event = EventFun_empty(),
        .update = SimpleFun_empty(),
        .ui = SimpleFun_make(ui),
    };
}
