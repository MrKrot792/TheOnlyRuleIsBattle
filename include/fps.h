#pragma once
#include <stdint.h>

// Very small and lightweight :3

typedef struct {
    uint32_t fps;
    float    fps_average;
    float    delta;
} FpsInfo;

void Fps_frameStart();
FpsInfo Fps_frameEnd();
