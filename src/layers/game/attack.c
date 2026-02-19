#include "layers/game/attack.h"
#include "layer.h"
#include "log.h"
#include "moves.h"
#include "render.h"
#include "texture.h"
#include "vec2.h"

#define TEXTURE_ATTACK_OVERLAY (uint8_t[2]){'#', '#'}

uint32_t move_index = 0;

void attackUi() {
    Render_drawTextAt((Vec2){0, RENDER_REAL_HEIGHT-2}, 
            "Index: %d, name: %s", 
            move_index, Moves_getAt(move_index).move.name);

    Render_drawTextureAtCamera(Vec2_zero(), Texture_create(TEXTURE_ATTACK_OVERLAY));
}

Layer layerGameAttack(uint32_t move_index_internal) {
    move_index = move_index_internal;
    Log(LOG_DEBUG, "Made an attack layer!");

    return (Layer){
        .init = InitFun_empty(),
        .deinit = SimpleFun_empty(),
        .event = EventFun_empty(),
        .render = SimpleFun_empty(),
        .update = SimpleFun_empty(),
        .ui = SimpleFun_make(attackUi),
    };
}
