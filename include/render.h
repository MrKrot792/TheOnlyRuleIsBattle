#pragma once
#include <ncurses.h>

// Render width, used for internal transformations
#define RENDER_WIDTH COLS
// Render height, used for internal transformations
#define RENDER_HEIGHT LINES

// Real width, can be used safetely by the user
#define RENDER_REAL_WIDTH RENDER_WIDTH/2
// Real height, can be used safetely by the user
#define RENDER_REAL_HEIGHT RENDER_HEIGHT

void Render_drawAll();
