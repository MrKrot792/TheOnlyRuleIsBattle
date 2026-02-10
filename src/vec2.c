#include <math.h>

#include "vec2.h"

Vec2 Vec2_create(float x, float y) { return (Vec2) {x, y}; }
Vec2 Vec2_zero() { return (Vec2) {0, 0}; }

Vec2 Vec2_add(Vec2 a, Vec2 b) { return (Vec2){a.x + b.x, a.y + b.y}; }
Vec2 Vec2_sub(Vec2 a, Vec2 b) { return (Vec2){a.x - b.x, a.y - b.y}; }
Vec2 Vec2_mul(Vec2 a, Vec2 b) { return (Vec2){a.x * b.x, a.y * b.y}; }
Vec2 Vec2_div(Vec2 a, Vec2 b) { return (Vec2){a.x / b.x, a.y / b.y}; }

Vec2 Vec2_scale(Vec2 a, float s) { return (Vec2){a.x * s, a.y * s}; }
float Vec2_dot(Vec2 a, Vec2 b) { return a.x * b.x + a.y * b.y; }

float Vec2_length(Vec2 a) { return sqrtf(a.x * a.x + a.y * a.y); }
Vec2 Vec2_normalize(Vec2 a) { float l = Vec2_length(a); return (Vec2){ a.x/l, a.y/l }; }
Vec2 Vec2_negate(Vec2 a) { return (Vec2){-a.x, -a.y}; }
