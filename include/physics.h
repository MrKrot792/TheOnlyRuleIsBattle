#pragma once

#include "character.h"

// Modifies the character directly
void Physics_simulate(Character* c);
// Returns the simulated copy
Character Physics_simulateCopy(const Character *c);
