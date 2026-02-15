#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef void (*SimpleFun_internal)();
typedef struct {
    bool present;
    void (*function)();
} SimpleFun;

typedef bool (*EventFun_internal)(int ch);
typedef struct {
    bool present;
    bool (*function)(int ch);
} EventFun;

// TODO: Make functions optional
typedef struct {
    SimpleFun init;
    SimpleFun deinit;

    SimpleFun update;
    SimpleFun render;

    // If returns false, then the events don't go lower
    EventFun event;
} Layer;

void SimpleFun_call(SimpleFun fun);
bool EventFun_call(EventFun fun, int ch);
SimpleFun SimpleFun_make(SimpleFun_internal fun);
EventFun EventFun_make(EventFun_internal fun);
SimpleFun SimpleFun_empty();
EventFun EventFun_empty();

// For interacting with the layer stack

// Returns the ID of a newly registered layer
uint32_t Layer_create(Layer layer);
void Layer_destroy(uint32_t id);
void Layer_transition(uint32_t id, Layer layer);

// Call these at their appropriate times
void Layers_update();
void Layers_render();
void Layers_events();
