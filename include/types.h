#ifndef TYPES_H
#define TYPES_H

typedef enum {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    PIECE_EMPTY,
} Piece;

typedef enum {
    WHITE = 0,
    BLACK = 1,
    ALL = 2,
} Color;

typedef enum {
    CASTLE_WHITE_KING = (1 << 0),
    CASTLE_WHITE_QUEEN = (1 << 1),
    CASTLE_BLACK_KING = (1 << 2),
    CASTLE_BLACK_QUEEN = (1 << 3),
} CastleRights;

#endif
