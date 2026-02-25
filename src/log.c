#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "log.h"

static FILE* logFile = NULL;
Log_Ring lastLog = {0};
#define EMPTY_STRING "[EMPTY  ]"

void Log_init() { 
    logFile = fopen(LOG_FILE, "a"); 
    for (int i = 0; i < LOG_LOG_UI_SIZE; i++) {
        lastLog.memory[i] = malloc(256);
        strcpy(lastLog.memory[i], EMPTY_STRING);
    }
}
void Log_deinit() { 
    fclose(logFile); 
    for (int i = 0; i < LOG_LOG_UI_SIZE; i++) {
        free(lastLog.memory[i]);
    }
}

// TODO: May be insecure? but idk
// Because \0 are annoying
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
    // Log file
    fprintf(logFile, "%s ", prefix); // Prefix
    vfprintf(logFile, message, ap);  // The message itself
    fprintf(logFile, "\n");          // The \n
    va_end(ap);

    // Pointer magic lmao
    va_list aq;
    va_start(aq, message);
    char *buf = lastLog.memory[lastLog.tail];
    size_t remaining = 256;
    int written;
    written = snprintf(buf, remaining, "%s ", prefix);
    buf += written;
    remaining -= written;
    written = vsnprintf(buf, remaining, message, aq);
    buf += written;
    remaining -= written;
    snprintf(buf, remaining, "\n");
    va_end(aq);

    if (lastLog.tail == LOG_LOG_UI_SIZE - 1) { lastLog.tail = 0; }
    else { lastLog.tail++; }
    fflush(logFile);
}
