#pragma once
#include <stdint.h>
#include <stdbool.h>

// TODO: Make functions optional
typedef struct {
    void (*init)();
    void (*deinit)();

    void (*update)();
    void (*render)();

    // If returns false, then the events don't go lower
    bool (*event)(int ch);
} Layer;

// For interacting with the layer stack

// Returns the ID of a newly registered layer
uint32_t Layer_create(Layer layer);
void Layer_destroy(uint32_t id);
void Layer_transition(uint32_t id, Layer layer);

// Call these at their appropriate times
void Layers_update();
void Layers_render();
void Layers_events();
