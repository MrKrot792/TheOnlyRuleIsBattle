#pragma once
#include <stdint.h>

#include "vec2.h"

#define TEXTURE_CHARACTER (Texture){'@', '@'}

typedef struct {
    Vec2 position;

    uint32_t hp;
} Character;

float* Character_getX();
float* Character_getY();
uint32_t* Character_getHp();
