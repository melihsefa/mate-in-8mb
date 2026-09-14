#include "position.h"
#include "bitboard.h"

Position position_init() {
    Position position;
    position.board = board_init();
    position.side_to_move = WHITE;
    position.castling_rights = 0x0F; // 0b1111 Each bit represents a different castling situation (Check 'types.h')
    position.en_passant = NO_SQUARE;
    position.halfmove_clock = 0;
    position.fullmove_number = 1;

    return position;
}

// Assumes legal moves
void position_make_move(Position *pos, Move move) {
    /* 
    TODO:
    1 Move pieces (remove 'from' add 'to')                                              DONE
    2 Remove captured pieces from 'to' (additional code for enpassant)                  DONE
    3 Handle promotion                                                                  DONE
    4 Handle castling                                                                   DONE
    5 Adjust side_to_move                                                               DONE
    6 Check castling rights                                                             DONE
    7 Handle en passant (Should set it after two square pawn moves)                     DONE
    8 Set halfmove_clock (set it to 0 if pawn moved or capture, increase otherwise)     DONE
    9 Set fullmove_number (increase it after black's move)                              DONE
    */

    // Handling promotion and moving the piece
    Piece placed_piece = move.piece;
    if(move.type == MOVE_PROMOTION) {
        placed_piece = move.promotion;
    }

    pos->board.bitboards[pos->side_to_move][move.piece] = 
        clear_bit(pos->board.bitboards[pos->side_to_move][move.piece], move.from);
    pos->board.all_pieces[pos->side_to_move] = 
        clear_bit(pos->board.all_pieces[pos->side_to_move], move.from);
    pos->board.all_pieces[ALL] = 
        clear_bit(pos->board.all_pieces[ALL], move.from);

    // Promotion is handled here
    pos->board.bitboards[pos->side_to_move][placed_piece] =
        set_bit(pos->board.bitboards[pos->side_to_move][placed_piece], move.to); 
    pos->board.all_pieces[pos->side_to_move] = 
        set_bit(pos->board.all_pieces[pos->side_to_move], move.to);
    pos->board.all_pieces[ALL] = 
        set_bit(pos->board.all_pieces[ALL], move.to);

    
    // Removing the captured piece aaccounting for en_passant possibility
    uint8_t captured_square = move.to;
    Piece captured_piece = PIECE_EMPTY;
    if(move.type == MOVE_EN_PASSANT) {
        if(pos->side_to_move == WHITE) {
            captured_square -= 8;
        } else {
            captured_square += 8;
        }
    }

    for(int i = 0; i < PIECE_EMPTY; i++) {
        if(get_bit(pos->board.bitboards[pos->side_to_move ^ 1][i], captured_square)) {
            // all_pieces[ALL] shouldn't be cleared. It is occupied by our move already
            pos->board.bitboards[pos->side_to_move ^ 1][i] = 
                clear_bit(pos->board.bitboards[pos->side_to_move ^ 1][i], captured_square);
            pos->board.all_pieces[pos->side_to_move ^ 1] = 
                clear_bit(pos->board.all_pieces[pos->side_to_move ^ 1], captured_square);

            // save the captured piece for castle rights check
            captured_piece = i;
            
        }
    }

    // Moving rook if castled
    if(move.type == MOVE_CASTLE) {
        uint8_t rook_from;
        uint8_t rook_to;

        if(move.to > move.from) {
            rook_from = move.from + 3;
            rook_to = move.from + 1;
        } else {
            rook_from = move.from - 4;
            rook_to = move.to -1;
        }

        pos->board.bitboards[pos->side_to_move][ROOK] = 
            clear_bit(pos->board.bitboards[pos->side_to_move][ROOK], rook_from);
        pos->board.all_pieces[pos->side_to_move] = 
            clear_bit(pos->board.all_pieces[pos->side_to_move], rook_from);
        pos->board.all_pieces[ALL] = 
            clear_bit(pos->board.all_pieces[ALL], rook_from);

        pos->board.bitboards[pos->side_to_move][ROOK] = 
            set_bit(pos->board.bitboards[pos->side_to_move][ROOK], rook_to);
        pos->board.all_pieces[pos->side_to_move] = 
            set_bit(pos->board.all_pieces[pos->side_to_move], rook_to);
        pos->board.all_pieces[ALL] = 
            set_bit(pos->board.all_pieces[ALL], rook_to);
    }

    // Removing the en_passant right.
    pos->en_passant = NO_SQUARE;


    // Handling the castling_rights and changing the sides
    if(move.piece == KING) {
        uint8_t castle_right_shift = pos->side_to_move * 2;
        // Setting both castle rights to zero using 0b1100
        pos->castling_rights = 
            pos->castling_rights & (0x0C >> castle_right_shift);
    }

    if(move.piece == ROOK) {
        uint8_t castle_right_shift = pos->side_to_move * 2;
        uint8_t side_decision = move.from & (uint8_t)1;
        castle_right_shift = castle_right_shift + side_decision;

        pos->castling_rights = 
            pos->castling_rights & (uint8_t)~(1 << castle_right_shift);
    }

    pos->side_to_move = pos->side_to_move ^ 1;

    if(captured_piece == ROOK && 
        (move.to == 0 || move.to == 7 || move.to == 56 || move.to == 63)) {
            
        uint8_t castle_right_shift = pos->side_to_move * 2;
        uint8_t side_decision = move.to & (uint8_t)1;
        castle_right_shift = castle_right_shift + side_decision;

        pos->castling_rights = 
            pos->castling_rights & (uint8_t)~(1 << castle_right_shift);
    }

    // Setting en_passant rights
    if(move.piece == PAWN && (move.to - move.from == 16 || move.to - move.from == -16)) {
        pos->en_passant = (uint8_t)((move.from + move.to) / 2);
    }

    // Increase halfmove_clock if no pawn pushed or no piece captured
    if(captured_piece != PIECE_EMPTY || move.piece == PAWN) {
        pos->halfmove_clock = 0;
    } else {
        pos->halfmove_clock += 1;
    }

    if(pos->side_to_move == WHITE) {
        pos->fullmove_number++;
    }
}

void position_unmake_move(Position *pos, Move move) {
    (void)pos;
    (void)move;
} 
