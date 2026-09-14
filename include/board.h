#include <stdint.h>
#include <stdio.h>
#include <types.h>

typedef struct {
    uint64_t bitboards[2][6];
    uint64_t all_pieces[3];
} Board;

Board init_board();
void print_board(Board board);

void move(Board *board, Color color, Piece piece, uint8_t from, uint8_t to);


static inline uint8_t get_bit(uint64_t bitboard, uint8_t bit_number) {
    return (uint8_t)((bitboard >> bit_number) & 1ULL);
}
static inline uint64_t set_bit(uint64_t bitboard, uint8_t bit_number) {
    return bitboard | (1ULL << bit_number);
}

static inline uint64_t clear_bit(uint64_t bitboard, uint8_t bit_number) {
    return bitboard & ~(1ULL << bit_number);
}

static inline int get_lsb(uint64_t bitboard){
    if (bitboard == 0) return -1;
    return __builtin_ctzll(bitboard);
}
