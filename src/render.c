#include <stdint.h>
#include <ncurses.h>
#include <stdarg.h>
#include <stdio.h>

#include "render.h"
#include "texture.h"
#include "vec2.h"
#include "camera.h"

// Changes `position` to it's position in camera's space
// This is somehow really slow
#define CAMERA(position) Vec2_sub((Vec2){(int32_t)position.x + (RENDER_WIDTH/4), \
                                         (int32_t)position.y + (RENDER_HEIGHT/2)}, \
                                         Camera_get())

// TODO: Too much Vec2_round
static uint8_t texture_buffer[2] = {0};
void Render_drawTextureAtCamera(Vec2 position, const Texture texture) {
    Render_drawTextureAt(CAMERA(Vec2_round(position)), texture);
}

void Render_drawTextureAt(Vec2 position, const Texture texture) {
    Render_drawTextureAtDecorated(Vec2_round(position), texture, 0x0); // no attributes
}

void Render_drawTextureAtDecoratedCamera(Vec2 position, const Texture texture, int attribute) {
    Render_drawTextureAtDecorated(CAMERA(Vec2_round(position)), texture, attribute);
}

// TODO: Texture type stores the attribute
// Only this function draws anything to the screen, any other drawTexture
// are just aliases, lol.
void Render_drawTextureAtDecorated(Vec2 position, const Texture texture, int attribute) {
    Vec2 camera = Vec2_round(position);

    Texture_get(texture_buffer, texture);

    mvaddch(camera.y, camera.x*2,   texture_buffer[0] | attribute);
    mvaddch(camera.y, camera.x*2+1, texture_buffer[1] | attribute);
}

void GCC_PRINTFLIKE(2, 3) Render_drawTextAt(Vec2 position, const char* text, ...) {
    va_list ap;
    va_start(ap, text);
    mvinch(position.y, position.x);
    vw_printw(stdscr, text, ap);
    va_end(ap);
}
