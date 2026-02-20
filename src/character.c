#include <stdlib.h>

#include "character.h"
#include "camera.h"

static Character* Player = {0};

void Character_init()   { Player = malloc(sizeof(&Player)); }
void Character_deinit() { free(Player); }

Character* Character_get() { return Player; }
