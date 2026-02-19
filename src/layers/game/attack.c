#include "layers/game/attack.h"
#include "layer.h"
#include "log.h"
#include "moves.h"
#include "render.h"
#include "texture.h"
#include "vec2.h"

#define TEXTURE_ATTACK_OVERLAY (uint8_t[2]){'#', '#'}

uint32_t move_index = 0;

Vec2 target = {0};

void attackUi() {
    Render_drawTextAt((Vec2){0, RENDER_REAL_HEIGHT-2}, 
            "Index: %d, name: %s", 
            move_index, Moves_getAt(move_index).move.name);

    Render_drawTextureAtCamera(Vec2_zero(), Texture_create(TEXTURE_ATTACK_OVERLAY));
    Render_drawTextureAtCamera(target, Texture_create(TEXTURE_ATTACK_OVERLAY));
}

bool attackEvent(int ch) {
    switch (ch) {
        case 'a':
            target.x--;
            break;
        case 'd':
            target.x++;
            break;
        case 'w':
            target.y--;
            break;
        case 's':
            target.y++;
            break;
    }
    return false;
}

Layer layerGameAttack(uint32_t move_index_internal) {
    move_index = move_index_internal;
    Log(LOG_DEBUG, "Made an attack layer!");

    return (Layer){
        .init = InitFun_empty(),
        .deinit = SimpleFun_empty(),
        .event = EventFun_make(attackEvent),
        .render = SimpleFun_empty(),
        .update = SimpleFun_empty(),
        .ui = SimpleFun_make(attackUi),
    };
}
