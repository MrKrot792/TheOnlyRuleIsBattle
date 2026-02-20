#pragma once
#include <stdint.h>

#include "vec2.h"

#define TEXTURE_CHARACTER (uint8_t[2]){'@', '@'}

typedef struct {
    Vec2 position;

    uint32_t hp;
} Character;

void Character_init();
void Character_deinit();

Character* Character_get();
