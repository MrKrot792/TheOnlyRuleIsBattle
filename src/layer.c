#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "layer.h"
#include "app.h"

typedef struct {
    Layer* data;
    uint32_t count;
} Stack;

// returns newly pushed layer's id
static uint32_t Stack_push(Stack* s, Layer d) {
    s->data = realloc(s->data, (s->count + 1) * sizeof(Layer));
    s->data[s->count] = d;
    s->count++;
    return s->count - 1;
}

static void Stack_pop(Stack* s) {
    if (s->count == 0) { return; }
    if (s->count != 1) {
        s->data = realloc(s->data, s->count - 1);
    }

    s->count--;
}

static void Stack_removeAt(Stack* s, uint32_t at) {
    for (int i = at; i > s->count - 1; i++) {
        if (i == s->count - 2) break;
        s->data[i] = s->data[i + 1];
    }
    s->data = realloc(s->data, s->count - 1);
    s->count--;
}

static void Stack_changeAt(Stack* s, uint32_t at, Layer new) {
    s->data[at] = new;
}

// TODO: better program break, with stacktrace
static Layer Stack_at(Stack* s, uint32_t at) {
    if (at >= s->count) {
        App_breakWithMessage(APP_SEGFAULT, "Segfault in Stack_at");
        return (Layer){0};
    }
    return s->data[at];
}

Stack layer_stack = {0};

uint32_t Layer_create(Layer layer) { 
    layer.init();
    return Stack_push(&layer_stack, layer); 
}
void Layer_destroy(uint32_t id) { 
    Stack_at(&layer_stack, id).deinit();
    Stack_removeAt(&layer_stack, id); 
}
void Layer_transition(uint32_t id, Layer layer) { 
    Stack_changeAt(&layer_stack, id, layer); 
}

void Layers_update() {
    for (int i = 0; i < layer_stack.count; i++) {
        Stack_at(&layer_stack, i).update();
    }
}
void Layers_render() {
    for (int i = 0; i < layer_stack.count; i++) {
        Stack_at(&layer_stack, i).render();
    }
}
void Layers_events() {
    int ch = getch();

    for (int i = 0; i < layer_stack.count; i++) {
        if (Stack_at(&layer_stack, i).event(ch)) break;
    }
}
