#pragma once
#include <ncurses.h>

#include "vec2.h"
#include "texture.h"

// Render width, used for internal transformations
#define RENDER_WIDTH COLS
// Render height, used for internal transformations
#define RENDER_HEIGHT LINES

// Real width, can be used safetely by the user
#define RENDER_REAL_WIDTH RENDER_WIDTH/2
// Real height, can be used safetely by the user
#define RENDER_REAL_HEIGHT RENDER_HEIGHT

void Render_drawTextureAt(Vec2 position, const Texture texture);
void Render_drawTextureAtCamera(Vec2 position, const Texture texture);
void Render_drawTextureAtDecorated(Vec2 position, const Texture texture, int attribute);
void Render_drawTextureAtDecoratedCamera(Vec2 position, const Texture texture, int attribute);
void GCC_PRINTFLIKE(2, 3) Render_drawTextAt(Vec2 position, const char* text, ...);
