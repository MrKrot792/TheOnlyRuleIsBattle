#include "character.h"

static Character GlobalCharacter = {0};

float* Character_getX()  { return &GlobalCharacter.position.x; }
float* Character_getY()  { return &GlobalCharacter.position.y; }
uint32_t* Character_getHp() { return &GlobalCharacter.hp; }
