#include <stdint.h>
#include <stdlib.h>

#include "blocks.h"
#include "texture.h"
#include "vec2.h"
#include "app.h"
#include "world.h"

static World GlobalWorld = {0};
// Fallbacking to this block, if segfaulting
static Block ErrorBlock = {0};

void World_init(uint32_t width, uint32_t height) { 
    GlobalWorld.data = malloc(sizeof(Block) * width * height);
    for (int i = 0; i < width * height; i++) {
        GlobalWorld.data[i] = Blocks_get(BLOCK_EMPTY);
    }

    GlobalWorld.height = height;
    GlobalWorld.width = width;

    ErrorBlock.texture = Texture_create(TEXTURE_ERROR);
    ErrorBlock.solid = true;
}

void World_deinit() { free(GlobalWorld.data); }

Vec2 World_getSize() { return (Vec2){GlobalWorld.width, GlobalWorld.height}; }
Block* World_getAt(Vec2 position) {
    if (position.x < 0) { 
        App_breakWithMessage(APP_SEGFAULT, "From: World_getAt, position.x < 0."); 
        return NULL;
    }
    if (position.y < 0) { 
        App_breakWithMessage(APP_SEGFAULT, "From: World_getAt, position.y < 0."); 
        return &ErrorBlock; 
    }
    if ((uint32_t)position.x > GlobalWorld.width) { 
        App_breakWithMessage(APP_SEGFAULT, 
                "From: World_getAt, position.x < World.width."); 
        return &ErrorBlock; 
    }
    if ((uint32_t)position.y > GlobalWorld.height) { 
        App_breakWithMessage(APP_SEGFAULT, 
                "From: World_getAt, position.y < World.height"); 
        return &ErrorBlock; 
    }

    return &GlobalWorld.data[(uint32_t)position.y * GlobalWorld.width + (uint32_t)position.x];
}
