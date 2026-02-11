#include "character.h"

static Character Player = {0};

void Character_setX(float x) { 
    Player.position.x = x; 
};

void Character_setY(float y) { 
    Player.position.y = y; 
}

float Character_getX() { return Player.position.x; }
float Character_getY() { return Player.position.y; }

Vec2 Character_getPosition() { return Player.position; }
void Character_setPosition(Vec2 position) { Player.position = position; }

uint32_t Character_getHp() { return Player.hp; }
void Character_setHp(uint32_t hp) { Player.hp = hp; }
