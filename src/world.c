#include <stdint.h>
#include <stdlib.h>

#include "vec2.h"
#include "app.h"
#include "world.h"

static World GlobalWorld = {0};

void World_init(uint32_t width, uint32_t height) { 
    GlobalWorld.data = malloc(sizeof(Block) * width * height);
    for (int i = 0; i < width * height; i++) {
        GlobalWorld.data[i].texture[0] = TEXTURE_DEFAULT[0];
        GlobalWorld.data[i].texture[1] = TEXTURE_DEFAULT[1];
    }

    GlobalWorld.height = height;
    GlobalWorld.width = width;
}

void World_deinit() { free(GlobalWorld.data); }

Vec2 World_getSize() { return (Vec2){GlobalWorld.width, GlobalWorld.height}; }

Block* World_getAt(Vec2 position) {
    if (position.x < 0) App_breakWithMessage(APP_SEGFAULT, "From: World_getAt, position.x < 0."); return NULL;
    if (position.y < 0) App_breakWithMessage(APP_SEGFAULT, "From: World_getAt, position.y < 0."); return NULL;
    if (position.x > GlobalWorld.width-1) App_breakWithMessage(APP_SEGFAULT, "From: World_getAt, position.x < World.width-1."); return NULL;
    if (position.y < GlobalWorld.height-1) App_breakWithMessage(APP_SEGFAULT, "From: World_getAt, position.y < World.height-1"); return NULL;
    return &GlobalWorld.data[(uint32_t)position.y * GlobalWorld.width + (uint32_t)position.x];
}
