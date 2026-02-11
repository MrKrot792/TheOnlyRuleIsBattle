#pragma once
#include <stdint.h>

#include "vec2.h"

#define TEXTURE_CHARACTER (Texture){'@', '@'}

typedef struct {
    Vec2 position;

    uint32_t hp;
} Character;

Vec2 Character_getPosition();
void Character_setPosition(Vec2 position);

uint32_t Character_getHp();
void Character_setHp(uint32_t hp);
