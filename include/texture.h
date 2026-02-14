// Usage:
// - Select a texture, prefixed with `TEXTURE_`, or make your own one like
// this: `(uint8_t[2]){'a', 'b'}`.
// - Pass the texture to `Texture_create()`.
// - To get texture's characters, use functions `Texture_get*`.

#pragma once
#include <stdint.h>

// Two encoded bytes, each one representing a char
typedef uint16_t Texture;

#define TEXTURE_EMPTY_BLOCK  (uint8_t[2]){'_', ' '}
#define TEXTURE_SOLID_BLOCK  (uint8_t[2]){'[', ']'}
#define TEXTURE_ERROR        (uint8_t[2]){'!', 'E'}

// Example use:
// `Texture_create(TEXTURE_EMPTY_BLOCK);`
Texture Texture_create(const uint8_t texture[2]);

void Texture_get(uint8_t buf[2], Texture texture);
// The caller own the memory!
uint8_t* Texture_getAlloc(Texture texture);
