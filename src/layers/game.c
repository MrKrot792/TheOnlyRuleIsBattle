#include "layers/game.h"

#include "app.h"
#include "render.h"
#include "character.h"
#include "world.h"

static void Render_drawCharacter() {
    Render_drawTextureAtCamera(Character_getPosition(), 
            Texture_create(TEXTURE_CHARACTER));
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

            Render_drawTextureAtCamera(position, block->texture);
        }
    }
}

static void init()        {}
static void deinit()      {}
static bool event(int ch) {
    switch (ch) {
        case 'a':
            Character_setPosition(Vec2_add(Character_getPosition(), (Vec2){-1, 0}));
            break;
        case 'd':
            Character_setPosition(Vec2_add(Character_getPosition(), (Vec2){1, 0}));
            break;
        case 'w':
            Character_setPosition(Vec2_add(Character_getPosition(), (Vec2){0, -1}));
            break;
        case 's':
            Character_setPosition(Vec2_add(Character_getPosition(), (Vec2){0, 1}));
            break;
    }
    return false;
}
static void render() {
    Render_drawWorld();
    Render_drawCharacter();
    Render_drawUI();
}
static void update()      {}

Layer layerGame() {
    return (Layer){
        .init = init,
        .deinit = deinit,
        .event = event,
        .render = render,
        .update = update,
    };
}
