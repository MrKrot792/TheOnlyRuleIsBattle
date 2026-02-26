#include <stdint.h>
#include <ncurses.h>

#include "layers/game/preview.h"
#include "layers/game/attack.h"
#include "layer.h"
#include "moves.h"
#include "render.h"
#include "vec2.h"

static int32_t selected_move = 0;
static int32_t max_moves = 0;
static uint32_t self_id = 0;

void init(uint32_t id) {
    max_moves = Moves_count();
    self_id = id;
}

bool event(int ch) {
    switch (ch) {
        case 'd':
            if(++selected_move == max_moves) { selected_move = 0; }
            break;
        case 'a':
            if(selected_move-- == 0) { selected_move = max_moves-1; }
            break;
        // Done selecting the move, now select parameters for it
        case ' ':
            Layer_transition(self_id, layerGameAttack(selected_move));
            break;
    }

    return false;
}

// rendering the moves
void previewUi() {
    mvinch(RENDER_REAL_HEIGHT-2, 0);
    clrtoeol();

    uint32_t width = RENDER_WIDTH / max_moves;

    for (int i = 0; i < max_moves; i++) {
        char selected_p = '|';
        char selected_s = '|';

        if (selected_move == i) {
            selected_p = '{';
            selected_s = '}';
            attron(A_BOLD | A_STANDOUT);
        }

        Render_drawTextAt((Vec2){width * i, RENDER_REAL_HEIGHT - 2}, "%c", selected_p);

        Render_drawTextAt((Vec2){(width * i) + 1, RENDER_REAL_HEIGHT - 2}, 
                "%-*s", width, Moves_getAt(i).move.name);

        Render_drawTextAt((Vec2){width * (i + 1) - 1, RENDER_REAL_HEIGHT - 2}, "%c", selected_s);

        if (selected_move == i) attroff(A_BOLD | A_STANDOUT);
    }
}

Layer layerGamePreview() {
    return (Layer){
        .init = InitFun_make(init),
        .deinit = SimpleFun_empty(),
        .event = EventFun_make(event),
        .render = SimpleFun_empty(),
        .update = SimpleFun_empty(),
        .ui = SimpleFun_make(previewUi),
    };
}
