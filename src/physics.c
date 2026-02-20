#include "physics.h"
#include "log.h"

void Physics_simulate(Character *c) {
    // Doing nothin'!
    Log(LOG_INFO, "Simulating the character...");
}

Character Physics_simulateCopy(const Character *c) {
    // Doing nothin'!
    Log(LOG_INFO, "Simulating the character... but different");
    return *c;
}
