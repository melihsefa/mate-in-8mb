#include "position.h"


int main() {
    Position pos = position_init();
    board_print(pos.board);

    return 0;
}