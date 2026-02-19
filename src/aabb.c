#include "include/aabb.h"

AABB AABB_fromCenteredRectangle(Vec2 position, Vec2 size) {
    return (AABB){
        .lower_bound = Vec2_sub(position, Vec2_scale(size, 1.f/2.f)),
        .upper_bound = Vec2_add(position, Vec2_scale(size, 1.f/2.f)),
    };
}

AABB AABB_fromRectangle(Vec2 position, Vec2 size) {
    return (AABB){
        .lower_bound = position,
        .upper_bound = Vec2_add(position, size),
    };
}

bool AABB_intersecting(AABB b1, AABB b2) {
    return (b1.lower_bound.x <= b2.upper_bound.x && 
            b1.upper_bound.x >= b2.lower_bound.x) &&
           (b1.lower_bound.y <= b2.upper_bound.y && 
            b1.upper_bound.y >= b2.lower_bound.y);
}
