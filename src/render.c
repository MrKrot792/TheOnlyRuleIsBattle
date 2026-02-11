#include <stdint.h>
#include <ncurses.h>
#include <stdarg.h>

#include "render.h"
#include "fps.h"
#include "world.h"
#include "character.h"
#include "app.h"
#include "vec2.h"

static void Render_drawTextureAt(Vec2 position, Texture texture) {
    int32_t x_camera = (int32_t)position.x + (RENDER_WIDTH/4);
    int32_t y_camera = (int32_t)position.y + (RENDER_HEIGHT/2);

    mvaddch(y_camera, x_camera*2,   texture[0]);
    mvaddch(y_camera, x_camera*2+1, texture[1]);
}

static void GCC_PRINTFLIKE(2, 3) Render_drawTextAt(Vec2 position, const char* text, ...) {
    va_list ap;
    va_start(ap, text);
    mvinch(position.y, position.x);
    vw_printw(stdscr, text, ap);
    va_end(ap);
}

static void Render_drawCharacter() {
    Render_drawTextureAt(Vec2_create(*Character_getX(), *Character_getY()), TEXTURE_CHARACTER);
}

static void Render_drawUI() {
    FpsInfo fps = App_getFps();
    Render_drawTextAt(Vec2_create(0, LINES-1),
            "HP: %d; POS: %Gx, %Gy; FPS: %d; Delta: %f;", 

            *Character_getHp(), 
            *Character_getX(), 
            *Character_getY(),
            fps.fps,
            fps.delta);
}

void Render_drawAll() {
    Render_drawCharacter();
    Render_drawUI();
}
