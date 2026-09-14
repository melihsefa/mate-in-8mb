#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "board.h"
#include "bitboard.h"

static int tests_run = 0;
static int tests_passed = 0;

#define CHECK(cond, msg) do {                           \
    tests_run++;                                        \
    if(cond) tests_passed++;                            \
    else printf("FAIL: %s (line %d)\n", msg, __LINE__); \
} while (0)
    

static void test_get_bit() {
    uint64_t bitboard = 0;

    CHECK(get_bit(bitboard, 0) == 0, "get_bit: bit 0 should be 0");
    CHECK(get_bit(bitboard, 63) == 0, "get_bit: bit 63 should be 0");

    bitboard = 1ULL;
    CHECK(get_bit(bitboard, 0) == 1, "get_bit: bit 0 should be 1");
    CHECK(get_bit(bitboard, 1) == 0, "get_bit: bit 1 should be 0");


    bitboard = 1ULL << 63;
    CHECK(get_bit(bitboard, 63) == 1, "get_bit: bit 63 should be 1");
    CHECK(get_bit(bitboard, 62) == 0, "get_bit: bit 62 should be 0");


    bitboard = ~0ULL;
    CHECK(get_bit(bitboard, 0) == 1, "get_bit: bit 0 should be 1");
    CHECK(get_bit(bitboard, 63) == 1, "get_bit: bit 63 should be 1");


    bitboard = 15ULL << 31;
    CHECK(get_bit(bitboard, 30) == 0, "get_bit: bit 30 should be 0");
    CHECK(get_bit(bitboard, 31) == 1, "get_bit: bit 31 should be 1");
    CHECK(get_bit(bitboard, 32) == 1, "get_bit: bit 32 should be 1");
    CHECK(get_bit(bitboard, 33) == 1, "get_bit: bit 33 should be 1");
    CHECK(get_bit(bitboard, 34) == 1, "get_bit: bit 34 should be 1");
    CHECK(get_bit(bitboard, 35) == 0, "get_bit: bit 35 should be 0");
}

static void test_set_bit() {
    uint64_t bitboard = 0ULL;

    bitboard = set_bit(bitboard, 0);
    CHECK(bitboard == 1ULL, "set_bit: bit 0 should be 1");
    
    bitboard = set_bit(bitboard, 5);
    CHECK(bitboard == ((1ULL << 5) | 1ULL), "set_bit: bit 1 and bit 5 should be 1");


    CHECK(bitboard == set_bit(bitboard, 5), "set_bit: setting an already-set bit changes nothing");
    
    bitboard = 0ULL;
    CHECK(set_bit(bitboard, 63) == (1ULL << 63), "set_bit: bit 63 should be 1");
}

static void test_clear_bit() {
    uint64_t bitboard = ~0ULL;
 
    bitboard = clear_bit(bitboard, 0);
    CHECK(get_bit(bitboard, 0) == 0, "clear_bit: bit 0 cleared");
    CHECK(get_bit(bitboard, 1) == 1, "clear_bit: bit 1 untouched");
 
    bitboard = clear_bit(bitboard, 63);
    CHECK(get_bit(bitboard, 63) == 0, "clear_bit: bit 63 cleared");
 
    CHECK(bitboard == clear_bit(bitboard, 0), "clear_bit: clearing an already-clear bit changes nothing");
 
    bitboard = 0;
    bitboard = clear_bit(bitboard, 10);
    CHECK(bitboard == 0, "clear_bit: clearing on an empty board stays empty");

}

static void test_get_lsb() {
    uint64_t bitboard = 0;
 
    CHECK(get_lsb(bitboard) == -1, "get_lsb: empty board should return -1");
 
    bitboard = 1ULL;
    CHECK(get_lsb(bitboard) == 0, "get_lsb: only bit 0 set");
 
    bitboard = 1ULL << 10;
    CHECK(get_lsb(bitboard) == 10, "get_lsb: only bit 10 set");
 
    bitboard = (1ULL << 10) | (1ULL << 20) | (1ULL << 40);
    CHECK(get_lsb(bitboard) == 10, "get_lsb: multiple bits set, lowest is 10");
 
    bitboard = 1ULL << 63;
    CHECK(get_lsb(bitboard) == 63, "get_lsb: only highest bit set");
 
    bitboard = ~0ULL;
    CHECK(get_lsb(bitboard) == 0, "get_lsb: all bits set, lsb is 0");

}


int main() {
    test_get_bit();
    test_set_bit();
    test_clear_bit();
    test_get_lsb();

    printf("\n%d/%d tests passed\n", tests_passed, tests_run);
    return (tests_passed == tests_run) ? 0 : 1;
}


