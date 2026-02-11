#include "fps.h"
#include <bits/time.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

static struct timespec frame_start;
static uint32_t frames_count;
static uint32_t frames;
static float elapsed;

void Fps_frameStart() {
    clock_gettime(CLOCK_MONOTONIC, &frame_start);
}

FpsInfo Fps_frameEnd() {
    struct timespec frame_end;
    clock_gettime(CLOCK_MONOTONIC, &frame_end);
    struct timespec difference = { frame_end.tv_sec - frame_start.tv_sec, 
                                   frame_end.tv_nsec - frame_start.tv_nsec };

    float d = ((float)difference.tv_sec + (float)difference.tv_nsec / (float)1.0e9);

    elapsed += d;
    frames_count++;

    if (elapsed >= 1.f) {
        elapsed = 0.f;
        frames = frames_count;
        frames_count = 0;
    }

    return (FpsInfo){
        .delta = d,
        .fps = frames,
        .fps_average = 1.0/d,
    };
}
