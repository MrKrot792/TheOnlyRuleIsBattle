#include "character.h"

static Character GlobalCharacter = {0};

uint32_t* Character_getX()  { return &GlobalCharacter.x; }
uint32_t* Character_getY()  { return &GlobalCharacter.y; }
uint32_t* Character_getHp() { return &GlobalCharacter.hp; }
