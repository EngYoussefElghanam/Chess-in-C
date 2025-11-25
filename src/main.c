#include <stdio.h>
#include "../include/board.h"

int main()
{
    char board[8][8];

    printf("Chess Game - Testing Board Functions\n\n");

    initialize_board(board);
    printf("Initial board:\n");
    print_board_simple(board);

    printf("\n--- Testing Functions ---\n");

    // Test get_piece_at
    char piece = get_piece_at(board, 0, 0);
    printf("Piece at (0,0): %c\n", piece); // Should be 'r' (white rook)

    // Test is_white_piece
    printf("Is 'r' white? %d\n", is_white_piece('r')); // Should be 1
    printf("Is 'R' white? %d\n", is_white_piece('R')); // Should be 0

    // Test is_square_empty
    printf("Is (0,0) empty? %d\n", is_square_empty(board, 0, 0)); // Should be 0
    printf("Is (4,4) empty? %d\n", is_square_empty(board, 4, 4)); // Should be 1

    // Test make_move - move white pawn from (1,4) to (3,4)
    printf("\n--- Moving white pawn from E2 to E4 ---\n");
    make_move(board, 1, 4, 3, 4);
    print_board_simple(board);

    return 0;
}