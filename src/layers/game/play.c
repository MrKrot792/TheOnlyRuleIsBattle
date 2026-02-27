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
#include "camera.h"

static uint32_t self_id = 0;
static uint32_t move_index = 0;

static float elapsed;

static Move move_cached;
static uint32_t frame;

static MoveParameters params;

static void init(uint32_t id) {
    elapsed = 0;
    self_id = id;
    move_cached = Moves_getAt(move_index).move;
    frame = 0;
}

static void update() {
    elapsed += App_getFps().delta;
    if (elapsed >= ( MOVE_DELTA )) {
        elapsed = 0;

        if (frame >= move_cached.duration) Layer_transition(self_id, 
                layerGamePreview());
        frame++;

        // TODO: Replace the placeholder move parameters with real ones
        move_cached.function(move_cached.duration, frame, params);
        Physics_simulate(Character_get());
        Camera_set(Character_get()->position);
    }
}

Layer layerGamePlay(uint32_t move_index_internal, MoveParameters params_internal) {
    move_index = move_index_internal;
    params = params_internal;

    return (Layer){
        .init = InitFun_make(init),
        .deinit = SimpleFun_empty(),
        .event = EventFun_empty(),
        .render = SimpleFun_empty(),
        .ui = SimpleFun_empty(),
        .update = SimpleFun_make(update),
    };
}
