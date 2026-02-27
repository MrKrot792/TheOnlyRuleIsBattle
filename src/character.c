#include <stdlib.h>

#include "character.h"
#include "camera.h"

static Character* Player = {0};

void Character_init()   { 
    Player = calloc(1, sizeof(Character));

    Player->hp = 100;
    Player->ruptureness = 380;
    Player->vultureness = 2;
}

Character* Character_get() { return Player; }
