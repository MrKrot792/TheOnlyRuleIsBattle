#pragma once
#include <ncurses.h>
#include "vec2.h"

// Render width, used for internal transformations
#define RENDER_WIDTH COLS
// Render height, used for internal transformations
#define RENDER_HEIGHT LINES

// Real width, can be used safetely by the user
#define RENDER_REAL_WIDTH RENDER_WIDTH/2
// Real height, can be used safetely by the user
#define RENDER_REAL_HEIGHT RENDER_HEIGHT

// Camera, just an alias
typedef Vec2 Camera;

void Render_drawAll();

// New camera's position is `CameraPosition + offset`
void Render_moveCamera(Vec2 offset);
Vec2 Render_getCameraPosition();
