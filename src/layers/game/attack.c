#include "layers/game/attack.h"
#include "layers/game/preview.h"
#include "layers/game/play.h"

#include "layer.h"
#include "log.h"
#include "moves.h"
#include "render.h"
#include "texture.h"
#include "vec2.h"
#include <ncurses.h>

#define TEXTURE_ATTACK_OVERLAY (uint8_t[2]){'#', '#'}
#define CENTERED(position) (Vec2){(int32_t)position.x + (RENDER_WIDTH/4), \
                                  (int32_t)position.y + (RENDER_HEIGHT/2)}

static uint32_t move_index = 0;
static uint32_t self_id = 0;

static Vec2 target = {0};

static void attackUi() {
    Render_drawTextAt((Vec2){0, RENDER_REAL_HEIGHT-2}, 
            "Move name: %s, duration: %d", 
            Moves_getAt(move_index).move.name, Moves_getAt(move_index).move.duration);

    if (Moves_getAt(move_index).move.paramsNeeded.vector) {
        Render_drawTextureAtDecorated(CENTERED(Vec2_zero()), Texture_create(TEXTURE_ATTACK_OVERLAY), A_ITALIC);
        Render_drawTextureAtDecorated(CENTERED(target), Texture_create(TEXTURE_ATTACK_OVERLAY), A_ITALIC);
    }
}

// TODO: The actual preview of the move, maybe???
static bool attackEvent(int ch) {
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

        // Cancel the move, back to selecting one
        case 'x':
            Layer_transition(self_id, layerGamePreview());
            break;

        // Selecting the move, and playing it!
        case ' ':
            Layer_transition(self_id, layerGamePlay(move_index, (MoveParameters){target}));
            break;
    }
    return false;
}

static void init(uint32_t id) {
    self_id = id;
    target = Vec2_zero();
}

Layer layerGameAttack(uint32_t move_index_internal) {
    move_index = move_index_internal;
    Log(LOG_DEBUG, "Made an attack layer!");

    return (Layer){
        .init = InitFun_make(init),
        .deinit = SimpleFun_empty(),
        .event = EventFun_make(attackEvent),
        .render = SimpleFun_empty(),
        .update = SimpleFun_empty(),
        .ui = SimpleFun_make(attackUi),
    };
}
