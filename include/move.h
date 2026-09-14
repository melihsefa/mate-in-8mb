#ifndef MOVE_H
#define MOVE_H

#include <stdint.h>
#include "types.h"

typedef enum {
    MOVE_NORMAL,
    MOVE_CASTLE,
    MOVE_EN_PASSANT,
    MOVE_PROMOTION,
} MoveType;

typedef struct {
    uint8_t from;
    uint8_t to;
    Piece piece;
    Piece promotion;
    MoveType type;
} Move;

#endif

