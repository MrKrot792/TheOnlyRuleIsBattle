#include <stdlib.h>

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

void World_deinit() { 
    free(GlobalWorld.data); 
}

Block* World_getAt(uint32_t x, uint32_t y) {
    return &GlobalWorld.data[y * GlobalWorld.width + x];
}
