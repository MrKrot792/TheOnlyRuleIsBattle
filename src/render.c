#include <stdint.h>
#include <ncurses.h>
#include <stdarg.h>

#include "render.h"
#include "world.h"
#include "character.h"
#include "app.h"

void RenderLocal_drawTextureAt(uint32_t x, uint32_t y, Texture texture) {
    mvaddch(y, x*2,   texture[0]);
    mvaddch(y, x*2+1, texture[1]);
}

void GCC_PRINTFLIKE(3, 4) RenderLocal_drawTextAt(uint32_t x, uint32_t y, const char* text, ...) {
    va_list ap;
    va_start(ap, text);
    mvinch(y, x);
    vw_printw(stdscr, text, ap);
    va_end(ap);
}

void RenderLocal_drawCharacter() {
    RenderLocal_drawTextureAt(*Character_getX(), *Character_getY(), TEXTURE_CHARACTER);
}

void RenderLocal_drawUI() {
    RenderLocal_drawTextAt(0, LINES-1, 
            "HP: %d; POS: %dx, %dy; FPS: %f;", 

            *Character_getHp(), 
            *Character_getX(), 
            *Character_getY(),
            App_getFps());
}

void Render_drawAll() {
    RenderLocal_drawCharacter();
    RenderLocal_drawUI();
}
