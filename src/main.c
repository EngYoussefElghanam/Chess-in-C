#include <stdio.h>
#include "../include/board.h"
#include "../include/display.h"
#include "../include/input.h"
#include "../include/moves.h"
#include "../include/game.h"
#include "../include/file_io.h"
#include "../include/history.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../include/types.h"

int main()
{
    char board[8][8];
    initialize_board(board);
    gameState Gs = {0};
    memcpy((&Gs)->board, board, sizeof(Gs.board));
    display_board(Gs.board);
    (&Gs)->is_white_turn = 1;
    (&Gs)->black_king_moved = 0;
    (&Gs)->white_king_moved = 0;
    (&Gs)->black_rook_a_moved = 0;
    (&Gs)->black_rook_h_moved = 0;
    (&Gs)->white_rook_h_moved = 0;
    (&Gs)->white_rook_a_moved = 0;
    LastMove dummy = {-1, -1, -1, -1, '\0'};
    (&Gs)->last_move = &dummy;
    (&Gs)->position_count = 0;
    return 0;
}