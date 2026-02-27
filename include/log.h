#pragma once
#include <stdint.h>

#define LOG_FILE "torib.log"

#define LOG_DEBUG   3
#define LOG_INFO    2
#define LOG_WARNING 1
#define LOG_ERROR   0

#define LOG_DEBUG_STRING   "[DEBUG  ]"
#define LOG_INFO_STRING    "[INFO   ]"
#define LOG_WARNING_STRING "[WARNING]"
#define LOG_ERROR_STRING   "[ERROR  ]"

#define LOG_LOG_UI_SIZE 8

typedef struct {
    uint32_t tail;
    char* memory[LOG_LOG_UI_SIZE];
} Log_Ring;

extern Log_Ring lastLog;

void Log_init();
void Log(uint32_t level, const char* message, ...);
void Log_deinit();
