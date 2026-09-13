#include <board.h>

Board init_board() {
    Board board;
    board.bitboards[WHITE][PAWN] = 0x000000000000FF00; 
    board.bitboards[BLACK][PAWN] = 0x00FF000000000000;
    board.bitboards[WHITE][KNIGHT] = 0x0000000000000042;
    board.bitboards[BLACK][KNIGHT] = 0x4200000000000000;
    board.bitboards[WHITE][BISHOP] = 0x0000000000000024;
    board.bitboards[BLACK][BISHOP] = 0x2400000000000000;
    board.bitboards[WHITE][ROOK] = 0x0000000000000081; 
    board.bitboards[BLACK][ROOK] = 0x8100000000000000;
    board.bitboards[WHITE][QUEEN] = 0x0000000000000008; 
    board.bitboards[BLACK][QUEEN] = 0x0800000000000000;
    board.bitboards[WHITE][KING] = 0x0000000000000010;
    board.bitboards[BLACK][KING] = 0x1000000000000000;
    board.all_pieces[WHITE] = 0x000000000000FFFF;
    board.all_pieces[BLACK] = 0xFFFF000000000000;
    board.all_pieces[ALL] = 0xFFFF00000000FFFF;

    return board;
}

void print_board(Board board) {
    char board_rep[65];
    for(int i = 0; i < 64; i++) {
        if(board.bitboards[WHITE][PAWN] & (1ULL << i)) {
            board_rep[i] = 'P';
            continue;
        }
        if(board.bitboards[BLACK][PAWN] & (1ULL << i)) {
            board_rep[i] = 'p';
            continue;
        }
        if(board.bitboards[WHITE][ROOK] & (1ULL << i)) {
            board_rep[i] = 'R';
            continue;
        }
        if(board.bitboards[BLACK][ROOK] & (1ULL << i)) {
            board_rep[i] = 'r';
            continue;
        }
        if(board.bitboards[WHITE][BISHOP] & (1ULL << i)) {
            board_rep[i] = 'B';
            continue;
        }
        if(board.bitboards[BLACK][BISHOP] & (1ULL << i)) {
            board_rep[i] = 'b';
            continue;
        }
        if(board.bitboards[WHITE][KNIGHT] & (1ULL << i)) {
            board_rep[i] = 'N';
            continue;
        }
        if(board.bitboards[BLACK][KNIGHT] & (1ULL << i)) {
            board_rep[i] = 'n';
            continue;
        }
        if(board.bitboards[WHITE][QUEEN] & (1ULL << i)) {
            board_rep[i] = 'Q';
            continue;
        }
        if(board.bitboards[BLACK][QUEEN] & (1ULL << i)) {
            board_rep[i] = 'q';
            continue;
        }        
        if(board.bitboards[WHITE][KING] & (1ULL << i)) {
            board_rep[i] = 'K';
            continue;
        }
        if(board.bitboards[BLACK][KING] & (1ULL << i)) {
            board_rep[i] = 'k';
            continue;
        }
        board_rep[i] = ' ';
    }
    board_rep[64] = '\0';
    

    // print rank 8 down to rank 1 (LERF: square = rank*8 + file, a1=0)
    for (int rank = 7; rank >= 0; rank--) {
        printf("%d ", rank + 1);
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            printf("%c ", board_rep[square]);
        }
        printf("\n");
    }
    printf("  a b c d e f g h\n");
}

uint8_t get_bit(uint64_t bitboard, uint8_t bit_number) {
    if(bitboard & (1ULL << bit_number)) {
        return 0;
    } else {
        return 1;
    }
}

void set_bit(uint64_t bitboard, uint8_t bit_number) {
    bitboard = bitboard | (1ULL << bit_number);
}

void clear_bit(uint64_t bitboard, uint8_t bit_number) {
    bitboard = bitboard & ~(1ULL << bit_number);
}

int get_lsb(uint64_t bitboard)
{
    return __builtin_ctzll(bitboard);
}

void move(Board board, Color color, Piece piece, uint8_t from, uint8_t to) {
    uint64_t bitboard = board.bitboards[color][piece];
    clear_bit(bitboard, from);
    set_bit(bitboard, to);
    bitboard = board.all_pieces[color];
    clear_bit(bitboard, from);
    set_bit(bitboard, to);
    bitboard = board.all_pieces[ALL];
    clear_bit(bitboard, from);
    set_bit(bitboard, to);
}