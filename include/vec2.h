#pragma once
#include <stdint.h>

typedef struct {
    float x;
    float y;
} Vec2;

Vec2 Vec2_create(float x, float y);
Vec2 Vec2_zero(void);

Vec2 Vec2_add(Vec2 a, Vec2 b);
Vec2 Vec2_sub(Vec2 a, Vec2 b);
Vec2 Vec2_mul(Vec2 a, Vec2 b);
Vec2 Vec2_div(Vec2 a, Vec2 b);

Vec2 Vec2_scale(Vec2 a, float s);
float Vec2_dot(Vec2 a, Vec2 b);

float Vec2_length(Vec2 a);
Vec2 Vec2_normalize(Vec2 a);
Vec2 Vec2_negate(Vec2 a);
