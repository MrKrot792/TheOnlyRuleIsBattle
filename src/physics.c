#include "physics.h"
#include "vec2.h"

#define DIV_BY 1.2f

void Physics_simulate(Character *c) {
    c->position = Vec2_add(c->velocity, c->position);
    c->velocity = Vec2_scale(c->velocity, 1.f/DIV_BY);

    c->ruptureness--;
    c->vultureness++;
}
