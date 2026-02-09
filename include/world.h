#pragma once
#include <stdint.h>

typedef char Texture[2];

#define TEXTURE_EMPTY_BLOCK (Texture){'_', ' '}
#define TEXTURE_SOLID_BLOCK (Texture){'[', ']'}

#define TEXTURE_DEFAULT TEXTURE_EMPTY_BLOCK

typedef struct {
    Texture texture;
} Block;

typedef struct {
    Block* data;

    uint32_t width;
    uint32_t height;
} World;

void World_init(uint32_t width, uint32_t height);
void World_deinit();

Block* World_getAt(uint32_t x, uint32_t y);
