#include <stdint.h>
#include <stdio.h>
#include <types.h>

typedef struct {
    uint64_t bitboards[2][6];
    uint64_t all_pieces[3];
} Board;

Board init_board();
void print_board(Board board);

uint8_t get_bit(uint64_t bitboard, uint8_t bit_number);
void set_bit(uint64_t bitboard, uint8_t bit_number);
void clear_bit(uint64_t bitboard, uint8_t bit_number);
int get_lsb(uint64_t bitboard);
void move(Board board, Color color, Piece piece, uint8_t from, uint8_t to);
