#include <stdio.h>
#include "board.h"
#include "display.h"
#include "input.h"
#include "moves.h"
#include "game.h"
#include "file_io.h"
#include "history.h"

int main()
{
    char board[8][8];

    printf("Chess Game - Testing Board Functions\n\n");

    initialize_board(board);
    print_board_simple(board);

    printf("\n--- Testing Functions ---\n");

    // Test get_piece_at
    char piece = get_piece_at(board, 0, 0);
    printf("Piece at (0,0): %c\n", piece);

    // Test is_white_piece
    printf("Is 'r' white? %d\n", is_white_piece('r'));
    printf("Is 'R' white? %d\n", is_white_piece('R'));

    // Test is_square_empty
    printf("Is (0,0) empty? %d\n", is_square_empty(board, 0, 0));
    printf("Is (4,4) empty? %d\n", is_square_empty(board, 4, 4));

    // Test make_move
    printf("\n--- Moving white pawn from E2 to E4 ---\n");
    make_move(board, 1, 4, 3, 4);
    print_board_simple(board);

    return 0;
}