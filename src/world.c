#include <stdlib.h>

#include "world.h"

void World_init(uint32_t width, uint32_t height) { 
    GlobalWorld.data = malloc(sizeof(Texture) * width * height);
    GlobalWorld.height = height;
    GlobalWorld.width = width;
}

void World_deinit() { 
    free(GlobalWorld.data); 
}

Texture* World_getAt(uint32_t x, uint32_t y) {
    return &GlobalWorld.data[y * GlobalWorld.width + x];
}
