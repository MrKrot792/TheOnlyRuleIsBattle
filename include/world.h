#pragma once
#include <stdint.h>
#include "vec2.h"
#include "blocks.h"

typedef struct {
    Block* data;

    uint32_t width;
    uint32_t height;
} World;

void World_init(uint32_t width, uint32_t height);
void World_deinit();

// Returns a pointer to the block at `position` position
Block* World_getAt(Vec2 position);
void World_setAt(Vec2 position, Block block);
Vec2 World_getSize();
