#include "texture.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

Texture Texture_create(const uint8_t texture[2]) {
    Texture result;
    memcpy(&result, texture, sizeof(result));
    return result;
}

void Texture_get(uint8_t buf[2], Texture texture) {
    memcpy(buf, &texture, 2);
}

// must free afterwards
uint8_t* Texture_getAlloc(Texture texture) {
    uint8_t* buf = malloc(2 * sizeof(uint8_t));
    memcpy(buf, &texture, 2);
    return buf;
}
