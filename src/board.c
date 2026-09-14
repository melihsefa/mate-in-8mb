#include "board.h"
#include "types.h"

Board board_init() {
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

void board_print(Board board) {
    for (int rank = 7; rank >= 0; rank--) {
        putchar((rank + 1) + '0');
        putchar(' ');

        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            char piece = ' ';
            if(board.bitboards[WHITE][PAWN] & (1ULL << square)) piece = 'P';
            else if(board.bitboards[BLACK][PAWN] & (1ULL << square)) piece = 'p';
            else if(board.bitboards[WHITE][ROOK] & (1ULL << square)) piece = 'R';
            else if(board.bitboards[BLACK][ROOK] & (1ULL << square)) piece = 'r';
            else if(board.bitboards[WHITE][BISHOP] & (1ULL << square)) piece = 'B';
            else if(board.bitboards[BLACK][BISHOP] & (1ULL << square)) piece = 'b';
            else if(board.bitboards[WHITE][KNIGHT] & (1ULL << square)) piece = 'N';
            else if(board.bitboards[BLACK][KNIGHT] & (1ULL << square)) piece = 'n';
            else if(board.bitboards[WHITE][QUEEN] & (1ULL << square)) piece = 'Q';
            else if(board.bitboards[BLACK][QUEEN] & (1ULL << square)) piece = 'q';    
            else if(board.bitboards[WHITE][KING] & (1ULL << square)) piece = 'K';
            else if(board.bitboards[BLACK][KING] & (1ULL << square)) piece = 'k';
            else piece = '-';
            
            putchar(piece);
            putchar(' ');
        }
        putchar('\n');
    }
    puts("  a b c d e f g h\n");
}