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

// Unused
// static void Stack_pop(Stack* s) {
//     if (s->count == 0) { return; }
//     if (s->count != 1) {
//         s->data = realloc(s->data, s->count - 1);
//     }
//
//     s->count--;
// }

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
    uint32_t id = Stack_push(&layer_stack, layer);  
    InitFun_call(layer.init, id);
    return id;
}
void Layer_destroy(uint32_t id) { 
    SimpleFun_call(Stack_at(&layer_stack, id).deinit);
    Stack_removeAt(&layer_stack, id); 
}
void Layer_transition(uint32_t id, Layer layer) { 
    SimpleFun_call(Stack_at(&layer_stack, id).deinit);
    Stack_changeAt(&layer_stack, id, layer); 
    InitFun_call(Stack_at(&layer_stack, id).init, id); // Oopsie, forgot to add this and was debugging two days!
}

void Layers_update() {
    for (int i = 0; i < layer_stack.count; i++) {
        SimpleFun_call(Stack_at(&layer_stack, i).update);
    }
}
void Layers_render() {
    for (int i = layer_stack.count - 1; i > 0; i--) {
        SimpleFun_call(Stack_at(&layer_stack, i).render);
    }
}
void Layers_ui() {
    for (int i = layer_stack.count - 1; i > 0; i--) {
        SimpleFun_call(Stack_at(&layer_stack, i).ui);
    }
}
void Layers_events() {
    int ch = getch();

    for (int i = 0; i < layer_stack.count; i++) {
        if (EventFun_call(Stack_at(&layer_stack, i).event, ch)) break;
    }
}

void SimpleFun_call(SimpleFun fun) {
    if (fun.present) fun.function();
}
bool EventFun_call(EventFun fun, int ch) {
    if (fun.present) return fun.function(ch);
    else return false;
}
void InitFun_call(InitFun fun, uint32_t id) {
    if (fun.present) return fun.function(id);
}

SimpleFun SimpleFun_make(SimpleFun_internal fun) {
    return (SimpleFun){ .function = fun, .present = true, }; 
}
EventFun EventFun_make(EventFun_internal fun) {
    return (EventFun){ .function = fun, .present = true, }; 
}
InitFun InitFun_make(InitFun_internal fun) {
    return (InitFun){ .function = fun, .present = true, }; 
}

SimpleFun SimpleFun_empty(){ 
    return (SimpleFun){ .function = NULL, .present = false }; 
}
EventFun EventFun_empty() {
    return (EventFun){ .function = NULL, .present = false };
}
InitFun InitFun_empty() {
    return (InitFun){ .function = NULL, .present = false };
}
