#include <stdint.h>
#include <stdlib.h>

#include "moves.h"

Move* moves = {0};
uint32_t moves_size = 0;

void Moves_register(Move move) {
    moves_size++;
    moves = realloc(moves, sizeof(Move) * moves_size);
    moves[moves_size - 1] = move;
}

void Moves_unregister() {
    free(moves);
}

MoveOptional Moves_getAt(uint32_t at) {
    if (at >= moves_size) return (MoveOptional){.is_present = false};
    return (MoveOptional){.move = moves[at], .is_present = true};
}

uint32_t Moves_count() {
    return moves_size;
}
