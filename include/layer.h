#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef void (*SimpleFun_internal)();
typedef struct {
    bool present;
    SimpleFun_internal function;
} SimpleFun;

typedef void (*InitFun_internal)(uint32_t id);
typedef struct {
    bool present;
    InitFun_internal function;
} InitFun;

typedef bool (*EventFun_internal)(int ch);
typedef struct {
    bool present;
    EventFun_internal function;
} EventFun;

typedef struct {
    InitFun   init;
    SimpleFun deinit;

    SimpleFun update;
    SimpleFun render;
    SimpleFun ui; // called after rendering

    // If returns false, then the events don't go lower
    EventFun event;
} Layer;

void SimpleFun_call(SimpleFun fun);
bool EventFun_call(EventFun fun, int ch);
void InitFun_call(InitFun fun, uint32_t id);

SimpleFun SimpleFun_make(SimpleFun_internal fun);
EventFun EventFun_make(EventFun_internal fun);
InitFun InitFun_make(InitFun_internal fun);

SimpleFun SimpleFun_empty();
EventFun EventFun_empty();
InitFun InitFun_empty();

// For interacting with the layer stack

// Returns the ID of a newly registered layer
uint32_t Layer_create(Layer layer);
void Layer_destroy(uint32_t id);
void Layer_transition(uint32_t id, Layer layer);

// Call these at their appropriate times
void Layers_update();
void Layers_render();
void Layers_events();
void Layers_ui();
