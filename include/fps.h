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

float Fps_timeToWait(FpsInfo info);
void Fps_setFramesPerSecond(uint32_t new_fps);
uint32_t Fps_getFramesPerSecond();
