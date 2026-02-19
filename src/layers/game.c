#include "layers/game.h"
#include "layers/game/preview.h"

#include "layer.h"
#include "character.h"
#include "render.h"
#include "world.h"
#include "moves.h"
#include "log.h"

static void drawCharacter() {
    Render_drawTextureAtCamera(Character_getPosition(), 
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

static MoveResult dash(uint32_t frame_max, uint32_t frame) {
    Log(LOG_DEBUG, "FM, F: %d, %d", frame_max, frame);
    return (MoveResult){ .is_present = false };
}

static MoveResult movePlaceholder(uint32_t frame_max, uint32_t frame) {
    return (MoveResult){ .is_present = false };
}

static uint32_t id = 0;
// TODO: Move this to another file or something?
static void init() {
    Moves_register((Move){
        .name = "Dash",
        .duration = 2,
        // TODO: function receiving interface's input, like vector, 
        // or just a number
        .function = dash,
    });

    for (int i = 0; i < 2; i++)
        Moves_register((Move){
            .name = "PlaceholderMove",
            .duration = 5,
            .function = movePlaceholder,
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
