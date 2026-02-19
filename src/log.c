#include "log.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

#define LOG_DEBUG_STRING   "[DEBUG]  "
#define LOG_INFO_STRING    "[INFO]   "
#define LOG_WARNING_STRING "[WARNING]"
#define LOG_ERROR_STRING   "[ERROR]  "

static FILE* logFile = NULL;

void Log_init() { logFile = fopen(LOG_FILE, "a"); }
void Log_deinit() { fclose(logFile); }

void GCC_PRINTFLIKE(2, 3) Log(uint32_t level, const char* message, ...) {
    char prefix[10];

    switch (level) {
        case LOG_DEBUG:
            strcpy(prefix, LOG_DEBUG_STRING);
            break;
        case LOG_INFO:
            strcpy(prefix, LOG_INFO_STRING);
            break;
        case LOG_WARNING:
            strcpy(prefix, LOG_WARNING_STRING);
            break;
        case LOG_ERROR:
            strcpy(prefix, LOG_ERROR_STRING);
            break;
    }

    va_list ap;
    va_start(ap, message);
    fprintf(logFile, "%s ", prefix);
    vfprintf(logFile, message, ap);
    fprintf(logFile, "\n");
    va_end(ap);

    fflush(logFile);
}
