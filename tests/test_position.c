#include <stdio.h>
#include "position.h"
#include "move.h"

static void print_position(const Position *pos)
{
    board_print(pos->board);

    printf("Side: %s\n",
           pos->side_to_move == WHITE ? "WHITE" : "BLACK");

    printf("Castling: %u\n", pos->castling_rights);
    printf("En passant: %u\n", pos->en_passant);
    printf("Halfmove: %u\n", pos->halfmove_clock);
    printf("Fullmove: %u\n", pos->fullmove_number);

    printf("\n");
}

int main(void)
{
    Position pos = position_init();

    printf("=== INITIAL ===\n");
    print_position(&pos);

    // 12 -> 28 (e2 -> e4)
    Move move = {
        .from = 12,
        .to = 28,
        .piece = PAWN,
        .promotion = PIECE_EMPTY,
        .type = MOVE_NORMAL
    };

    position_make_move(&pos, move);

    printf("=== 12 -> 28 ===\n");
    print_position(&pos);

    // 52 -> 36 (e7 -> e5)
    move.from = 52;
    move.to = 36;
    move.piece = PAWN;
    move.type = MOVE_NORMAL;

    position_make_move(&pos, move);

    printf("=== 52 -> 36 ===\n");
    print_position(&pos);

    // 6 -> 21 (g1 -> f3)
    move.from = 6;
    move.to = 21;
    move.piece = KNIGHT;
    move.type = MOVE_NORMAL;

    position_make_move(&pos, move);

    printf("=== 6 -> 21 ===\n");
    print_position(&pos);

    // 57 -> 42 (b8 -> c6)
    move.from = 57;
    move.to = 42;
    move.piece = KNIGHT;
    move.type = MOVE_NORMAL;

    position_make_move(&pos, move);

    printf("=== 57 -> 42 ===\n");
    print_position(&pos);

    return 0;
}