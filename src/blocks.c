#include <ncurses.h>
#include <stdlib.h>
#include <stdint.h>

#include "blocks.h"
#include "texture.h"

Block* registredBlocks = NULL;

// Registering the blocks so that we can get them later
void Blocks_init() {
    registredBlocks = malloc(sizeof(Block) * BLOCK_COUNT);

    registredBlocks[BLOCK_EMPTY] = (Block){
        .texture = Texture_create(TEXTURE_EMPTY_BLOCK),
        .solid = false,
    };
    registredBlocks[BLOCK_SOLID] = (Block){
        .texture = Texture_create(TEXTURE_SOLID_BLOCK),
        .solid = true,
    };

    /*
     * New blocks go here
     */
}

void Blocks_deinit() {
    free(registredBlocks);
}

Block Blocks_get(uint32_t index) {
    if (index > BLOCK_COUNT - 1) return (Block){
        .texture = Texture_create(TEXTURE_ERROR),
        .solid = false,
    };

    return registredBlocks[index];
}
