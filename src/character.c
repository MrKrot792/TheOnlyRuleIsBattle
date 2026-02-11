#include "character.h"

static Character Player = {0};

float* Character_getX()       { return &Player.position.x; }
float* Character_getY()       { return &Player.position.y; }
Vec2* Character_getPosition() { return &Player.position; }
uint32_t* Character_getHp()   { return &Player.hp; }
