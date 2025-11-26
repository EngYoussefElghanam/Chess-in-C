#include "../include/moves.h"
#include "../include/board.h"
#include <stdlib.h>
// knight moves in L shape regardless of what is in the way
// except if there's a team-mate on the desired square this will be handled in the main move validation
int is_valid_knight_move(int from_row, int from_col, int to_row, int to_col)
{
    int row_diff = abs(to_row - from_row);
    int col_diff = abs(to_col - from_col);
    return ((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2)); // this ensures that it is L shaped move
}
// checking if path is clear (no piece is on the way)
#include <stdlib.h> // Add this at top for abs()

// Check if path between two squares is clear (no pieces blocking)
int is_path_clear(char board[8][8], int from_row, int from_col, int to_row, int to_col)
{
    int row_direction = 0;
    int col_direction = 0;

    // Determine direction of movement
    if (to_row > from_row)
    {
        row_direction = 1; // Moving up
    }
    else if (to_row < from_row)
    {
        row_direction = -1; // Moving down
    }

    if (to_col > from_col)
    {
        col_direction = 1; // Moving right
    }
    else if (to_col < from_col)
    {
        col_direction = -1; // Moving left
    }

    // Start checking from the square AFTER the starting position
    int current_row = from_row + row_direction;
    int current_col = from_col + col_direction;

    // Check each square until we reach destination (don't check destination itself)
    while (current_row != to_row || current_col != to_col)
    {
        if (!is_square_empty(board, current_row, current_col))
        {
            return 0; // Path is blocked
        }
        current_row += row_direction;
        current_col += col_direction;
    }

    return 1; // Path is clear
}
// moves in straight line and the oath has to be clear
int is_valid_rook_move(char board[8][8], int from_row, int from_col, int to_row, int to_col)
{
    return ((from_col == to_col && from_row != to_row) || (from_col != to_col && from_row == to_row)) && is_path_clear(board, from_row, from_col, to_row, to_col);
}
// moves in diagonal and path has to be clear
int is_valid_bishop_move(char board[8][8], int from_row, int from_col, int to_row, int to_col)
{
    int row_diff = abs(to_row - from_row);
    int col_diff = abs(to_col - from_col);

    // Diagonal row_diff must equal col_diff (and both must be non-zero)
    return (row_diff == col_diff && row_diff != 0) && is_path_clear(board, from_row, from_col, to_row, to_col);
}

// moves like rook or bishob
int is_valid_queen_move(char board[8][8], int from_row, int from_col, int to_row, int to_col)
{
    return is_valid_bishop_move(board, from_row, from_col, to_row, to_col) || is_valid_rook_move(board, from_row, from_col, to_row, to_col);
}
