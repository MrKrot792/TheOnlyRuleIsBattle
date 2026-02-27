#pragma once
#include <stdint.h>

#include "aabb.h"

#define MOVE_FRAMES 30.f // Per second
#define MOVE_DELTA  1.f / MOVE_FRAMES

// May be an attack (AABB + damage) or just nothing, then the function does
// everything by itself
typedef struct {
    AABB    colider;
    int32_t damage;
    bool    is_present;
} MoveResult;

typedef struct {
    bool vector; // Vec2
    // Commented this one because it's not implemented yet
    //bool number;
} MoveParametersNeeded;

typedef struct {
    Vec2 vector;
} MoveParameters;

typedef struct {
    // To display this in the UI.
    const char* name;
    // In frames.
    uint32_t duration;
    // The function can access everything it wants using global functions.
    // The `frame` parameter indicates 
    MoveResult (*function)(uint32_t max_frame, uint32_t frame, MoveParameters params);
    MoveParametersNeeded paramsNeeded;
} Move;

typedef struct {
    Move move;
    bool is_present;
} MoveOptional;

void Moves_register(Move move);
// Basically freeing everything
void Moves_unregisterAll();
// May return a null value, then `at` was out of bounds.
MoveOptional Moves_getAt(uint32_t at);
uint32_t Moves_count();
