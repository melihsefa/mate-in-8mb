#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint64_t bitboards[2][6];
    uint64_t all_pieces[3];
} Board;

Board board_init();
void board_print(Board board);

#endif
