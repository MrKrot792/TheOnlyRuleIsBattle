#pragma once
#include <stdint.h>

typedef char Texture[2];

typedef struct {
    Texture* data;
    uint32_t width;
    uint32_t height;
} World;

void World_init(uint32_t width, uint32_t height);
void World_deinit();

Texture* World_getAt(uint32_t x, uint32_t y);
