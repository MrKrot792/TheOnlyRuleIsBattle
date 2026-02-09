#pragma once
#include <stdint.h>

#define TEXTURE_CHARACTER (Texture){'@', '@'}

typedef struct {
    uint32_t x;
    uint32_t y;

    uint32_t hp;
} Character;

uint32_t* Character_getX();
uint32_t* Character_getY();
uint32_t* Character_getHp();
