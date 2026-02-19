#pragma once
#include "vec2.h"

typedef struct {
    Vec2 lower_bound;
    Vec2 upper_bound;
} AABB;

// Where .position equal upper-left corner
AABB AABB_fromRectangle(Vec2 position, Vec2 size);
// Where .position equal the center of the rectangle
AABB AABB_fromCenteredRectangle(Vec2 position, Vec2 size);
bool AABB_intersecting(AABB b1, AABB b2);
