#ifndef POSITION_H
#define POSITION_H

#include <stdint.h>
#include "board.h"
#include "move.h"

#define NO_SQUARE 64

typedef struct {
    Board board;

    uint8_t side_to_move;
    uint8_t castling_rights;
    uint8_t en_passant;
    uint16_t halfmove_clock;
    uint16_t fullmove_number;
} Position;

Position position_init();

void position_make_move(Position *pos, Move move);
void position_unmake_move(Position *pos, Move move);

#endif