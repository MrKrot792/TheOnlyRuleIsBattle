#pragma once
#include <stdint.h>

#include "vec2.h"

#define TEXTURE_CHARACTER (uint8_t[2]){'@', '@'}

typedef struct {
    // Ruptureness 'n vultureness
    uint32_t ruptureness;
    uint32_t vultureness;
    uint32_t hp;

    Vec2 position;
    Vec2 velocity;
} Character;

void Character_init();
void Character_deinit();

Character* Character_get();
