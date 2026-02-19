#include "fps.h"
#include <bits/time.h>
#include <stdint.h>
#include <time.h>

static struct timespec frame_start;
static uint32_t frames_count;
static uint32_t frames;
static float elapsed;

static uint32_t target_fps = 60; // can be modified

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

// TODO: This is too buggy, for some reason
float Fps_timeToWait(FpsInfo info) {
    float result = 1.0 / (float)target_fps - info.delta;
    if (result > 0) return result; else return 0.0;
}

void Fps_setFramesPerSecond(uint32_t new_fps) { target_fps = new_fps; }
uint32_t Fps_getFramesPerSecond()             { return target_fps; }
