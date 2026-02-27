#include "layers/game.h"
#include "layers/game/preview.h"

#include "layer.h"
#include "character.h"
#include "log.h"
#include "render.h"
#include "vec2.h"
#include "world.h"
#include "moves.h"

#include <stdbool.h>

static void drawCharacter() {
    Render_drawTextureAtCamera(Character_get()->position, 
            Texture_create(TEXTURE_CHARACTER));
}

static void drawWorld() {
    const Vec2 size = World_getSize();
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            const Vec2 position = Vec2_create(j, i);
            const Block *block = World_getAt(position);

            Render_drawTextureAtCamera(position, block->texture);
        }
    }
}

static void render() {
    drawWorld();
    drawCharacter();
}

static MoveResult dash(uint32_t frame_max, uint32_t frame, MoveParameters params) {
    Log(LOG_DEBUG, "Params: %fx %fy", params.vector.x, params.vector.y);

    Character_get()->velocity = Vec2_scale(params.vector, MOVE_DELTA * 5.f);
    return (MoveResult){ .is_present = false };
}

static MoveResult wait(uint32_t frame_max, uint32_t frame, MoveParameters params) {
    return (MoveResult){ .is_present = false };
}

static uint32_t id = 0;
// TODO: Move this to another file or something?
static void init() {
    Moves_register((Move){
        .name = "Dash",
        .duration = 4,
        .paramsNeeded = { .vector = true },
        .function = dash,
    });

    Moves_register((Move){
        .name = "Wait",
        .duration = 1,
        .paramsNeeded = {0}, // No params params needed
        .function = wait,
    });

    id = Layer_create(layerGamePreview());
}

static void deinit() {
    Layer_destroy(id);
}

Layer layerGame() {
    return (Layer){
        .init = InitFun_make(init),
        .deinit = SimpleFun_make(deinit),
        .event = EventFun_empty(),
        .render = SimpleFun_make(render),
        .update = SimpleFun_empty(),
        .ui = SimpleFun_empty(),
    };
}
