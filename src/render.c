#include <stdint.h>
#include <ncurses.h>

#include "render.h"
#include "world.h"
#include "character.h"

void RenderLocal_drawTextureAt(uint32_t x, uint32_t y, Texture texture) {
    mvaddch(y, x*2,   texture[0]);
    mvaddch(y, x*2+1, texture[1]);
}

void RenderLocal_drawCharacter() {
    RenderLocal_drawTextureAt(*Character_getX(), *Character_getY(), TEXTURE_CHARACTER);
}

void Render_drawAll() {
    RenderLocal_drawCharacter();
}
