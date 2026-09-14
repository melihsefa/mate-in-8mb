#include "position.h"
#include "bitboard.h"

Position position_init() {
    Position position;
    position.board = board_init();
    position.side_to_move = WHITE;
    position.castling_rights = 0b1111; // Each bit represents a different castling situation (Check 'types.h')
    position.en_passant = NO_SQUARE;
    position.halfmove_clock = 0;
    position.fullmove_number = 1;

    return position;
}

void position_make_move(Position *pos, Move move) {
    /* 
    TODO:
    1 Move pieces (remove 'from' add 'to')
    2 Remove captured pieces from to (additional code for enpassant)
    3 Handle promotion
    4 Handle castling
    5 Adjust side_to_move
    6 Check castling rights
    7 Handle en passant (Should set it after two square pawn moves)
    8 Set halfmove_clock (set it to 0 if pawn moved or capture, increase otherwise)
    9 Set fullmove_number (increase it after black's move)
    */   
}

void position_unmake_move(Position *pos, Move move) {

} 
