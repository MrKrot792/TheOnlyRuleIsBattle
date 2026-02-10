#pragma once
#include <ncurses.h>

#define APP_OK 0
#define APP_ERROR -1

#define WORLD_WIDTH 800
#define WORLD_HEIGHT 800

void App_init();
void App_deinit();

// Returns an error, if there's any, if there weren't any erros, returns 0 (APP_OK)
int App_loop();
