#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "texture.h"

enum BlockIndices {
    BLOCK_EMPTY,
    BLOCK_SOLID,

    // Reserved
    BLOCK_COUNT
};

typedef struct {
    Texture texture;
    bool solid;
} Block;

// Must call this before using any blocks
void Blocks_init();
Block Blocks_get(uint32_t index);
