#include <stdlib.h>

#include "world.h"

const Texture TEXTURE_EMPTY_BLOCK = { '_', ' ' };
const Texture TEXTURE_CHARACTER =   { '@', '@' };
const Texture TEXTURE_SOLID_BLOCK = { '[', ']' };

#define TEXTURE_DEFAULT TEXTURE_EMPTY_BLOCK

World GlobalWorld = {0};

void World_init(uint32_t width, uint32_t height) { 
    GlobalWorld.data = malloc(sizeof(Texture) * width * height);
    for (int i = 0; i < width * height; i++) {
        GlobalWorld.data[i][0] = TEXTURE_DEFAULT[0];
        GlobalWorld.data[i][1] = TEXTURE_DEFAULT[1];
    }

    GlobalWorld.height = height;
    GlobalWorld.width = width;
}

void World_deinit() { 
    free(GlobalWorld.data); 
}

Texture* World_getAt(uint32_t x, uint32_t y) {
    return &GlobalWorld.data[y * GlobalWorld.width + x];
}
