#include <stdint.h>
#include <ncurses.h>
#include <stdarg.h>
#include <stdio.h>

#include "render.h"
#include "fps.h"
#include "world.h"
#include "character.h"
#include "app.h"
#include "vec2.h"
#include "camera.h"

// Changes `position` to it's position in camera's space
// This is somehow really slow
#define CAMERA(position) Vec2_sub((Vec2){(int32_t)position.x + (RENDER_WIDTH/4), \
                                         (int32_t)position.y + (RENDER_HEIGHT/2)}, Camera_get())

static void Render_drawTextureAt(Vec2 position, const Texture texture) {
    Vec2 camera = CAMERA(position);

    mvaddch(camera.y, camera.x*2,   texture[0]);
    mvaddch(camera.y, camera.x*2+1, texture[1]);
}

static void GCC_PRINTFLIKE(2, 3) Render_drawTextAt(Vec2 position, const char* text, ...) {
    va_list ap;
    va_start(ap, text);
    mvinch(position.y, position.x);
    vw_printw(stdscr, text, ap);
    va_end(ap);
}

static void Render_drawCharacter() {
    Render_drawTextureAt(Character_getPosition(), TEXTURE_CHARACTER);
}

static void Render_drawUI() {
    FpsInfo fps = App_getFps();
    Vec2 position = Character_getPosition();
    Render_drawTextAt(Vec2_create(0, RENDER_REAL_HEIGHT - 1),
            "HP: %d; POS: %Gx, %Gy; FPS: %d; Delta: %f;", 

            Character_getHp(), 
            position.x, position.y,
            fps.fps, fps.delta);
}

static void Render_drawWorld() {
    const Vec2 size = World_getSize();
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            const Vec2 position = Vec2_create(j, i);
            const Block *block = World_getAt(position);

            Render_drawTextureAt(position, block->texture);
        }
    }
}

void Render_drawAll() {
    Render_drawWorld();
    Render_drawCharacter();
    Render_drawUI();
}
