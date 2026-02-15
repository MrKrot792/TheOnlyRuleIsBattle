#include "character.h"
#include "camera.h"

static Character Player = {0};

Vec2 Character_getPosition() { return Player.position; }
void Character_setPosition(Vec2 position) { 
    Player.position = position; 
    Camera_set(position);
}

uint32_t Character_getHp() { return Player.hp; }
void Character_setHp(uint32_t hp) { Player.hp = hp; }
