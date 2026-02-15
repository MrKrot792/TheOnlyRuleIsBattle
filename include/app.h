#pragma once
#include "fps.h"
#include <ncurses.h>

#define APP_OK 0
#define APP_GENERIC_ERROR -1
#define APP_SEGFAULT -2

#define WORLD_WIDTH 800
#define WORLD_HEIGHT 800

void App_init();
void App_deinit();
// Returns an error, if there's any, if there weren't any erros, returns 0 (APP_OK)
int App_loop();

// Errors
void App_break(int code);
void App_breakWithMessage(int code, const char* message);
const char* App_errno();
bool App_isErrorMessagePresent();

// Helpers
FpsInfo App_getFps();
