#pragma once
#include <stdint.h>
#include <sys/time.h>

// Very small and lightweight :3

typedef struct {
    uint32_t fps;
    float    fps_average;
    float    delta;
} FpsInfo;

typedef struct {
    // Can be changed manually, but preferably change it using a function
    uint32_t target_fps;

    struct timespec frame_start;
    uint32_t frames_count;
    uint32_t frames;
    float elapsed;
} FpsState;

// Creates a state. Because it does not allocate anything, no need to free.
extern FpsState Fps_create();

extern void Fps_frameStart(FpsState* state);
extern FpsInfo Fps_frameEnd(FpsState* state);

extern float Fps_timeToWait(const FpsState* state, FpsInfo info);
extern void Fps_setFramesPerSecond(FpsState* state, uint32_t new_fps);
extern uint32_t Fps_getFramesPerSecond(const FpsState* state);

#ifdef FPS_IMPLEMENTATION
#include <time.h>

FpsState Fps_create() {
    return (FpsState){
        .target_fps = 60,
        .frame_start = {0},
        .frames_count = 0,
        .frames = 0,
        .elapsed = 0,
    };
}

void Fps_frameStart(FpsState* state) {
    clock_gettime(CLOCK_MONOTONIC, &state->frame_start);
}

FpsInfo Fps_frameEnd(FpsState* state) {
    struct timespec frame_end;
    clock_gettime(CLOCK_MONOTONIC, &frame_end);
    struct timespec difference = { frame_end.tv_sec - state->frame_start.tv_sec, 
                                   frame_end.tv_nsec - state->frame_start.tv_nsec };

    float d = ((float)difference.tv_sec + (float)difference.tv_nsec / (float)1.0e9);

    state->elapsed += d;
    state->frames_count++;

    if (state->elapsed >= 1.f) {
        state->elapsed = 0.f;
        state->frames = state->frames_count;
        state->frames_count = 0;
    }

    return (FpsInfo){
        .delta = d,
        .fps = state->frames,
        .fps_average = 1.0/d,
    };
}

// TODO: This is too buggy, for some reason
float Fps_timeToWait(const FpsState* state, FpsInfo info) {
    float result = 1.0 / (float)state->target_fps - info.delta;
    if (result > 0) return result; else return 0.0;
}

void Fps_setFramesPerSecond(FpsState* state, uint32_t new_fps) { state->target_fps = new_fps; }
uint32_t Fps_getFramesPerSecond(const FpsState* state)         { return state->target_fps; }
#endif // FPS_IMPLEMENTATION
