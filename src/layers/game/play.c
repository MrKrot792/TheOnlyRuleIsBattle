#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>

#include "layers/game/play.h"
#include "layers/game/preview.h"
#include "layer.h"

#include "app.h"
#include "character.h"
#include "moves.h"
#include "physics.h"
#include "render.h"
#include "texture.h"

#define PHYSIC_FRAMES 5.f // Per second

static uint32_t self_id = 0;
static uint32_t move_index = 0;

static float elapsed;
static bool frame_trigger;

static Move move_cached;
static uint32_t frame;

static void init(uint32_t id) {
    elapsed = 0;
    frame_trigger = false;
    self_id = id;
    move_cached = Moves_getAt(move_index).move;
    frame = 0;
}

static void update() {
    elapsed += App_getFps().delta;
    if (elapsed >= ( 1.f / PHYSIC_FRAMES )) {
        frame_trigger = true;
        elapsed = 0;

        if (frame >= move_cached.duration) Layer_transition(self_id, 
                layerGamePreview());
        frame++;
    }
}

static void render() {
    if (frame_trigger) {
        // TODO: Replace the placeholder move parameters with real ones
        move_cached.function(move_cached.duration, frame, (MoveParameters){0});
        Physics_simulate(Character_get());
        frame_trigger = false;
    }

    Render_drawTextureAtDecoratedCamera(Character_get()->position, Texture_create(TEXTURE_CHARACTER), A_ITALIC);
}

Layer layerGamePlay(uint32_t move_index_internal) {
    move_index = move_index_internal;

    return (Layer){
        .init = InitFun_make(init),
        .deinit = SimpleFun_empty(),
        .event = EventFun_empty(),
        .render = SimpleFun_make(render),
        .ui = SimpleFun_empty(),
        .update = SimpleFun_make(update),
    };
}
