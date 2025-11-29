#include "../include/moves.h"
#include "../include/board.h"
#include <stdlib.h>
#include <ctype.h>
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

// moves one square in any direction
int is_valid_king_move(int from_row, int from_col, int to_row, int to_col)
{
    int condition1 = (abs(from_col - to_col) == 1 && abs(from_row - to_row) == 0);
    int condition2 = (abs(from_row - to_row) == 1 && abs(from_col - to_col) == 0);
    int condition3 = (abs(from_row - to_row) == 1 && abs(from_col - to_col) == 1);
    // notice we didn't include path clear cause it is only one square no paths
    // about if there's a teammate in the desired square or there's a check we will handle that later
    return (condition1 || condition2 || condition3);
}

int is_valid_pawn_move(char board[8][8], int from_row, int from_col, int to_row, int to_col, int is_white,
                       LastMove *last_move)
{
    int row_diff = to_row - from_row;
    int col_diff = to_col - from_col;
    int abs_col_diff = abs(col_diff);

    // WHITE PAWN
    if (is_white)
    {
        if (row_diff <= 0)
            return 0;

        // Normal forward move
        if (row_diff == 1 && col_diff == 0)
        {
            return is_square_empty(board, to_row, to_col);
        }

        // First move: 2 squares
        if (row_diff == 2 && col_diff == 0 && from_row == 1)
        {
            return is_square_empty(board, to_row, to_col) && is_path_clear(board, from_row, from_col, to_row, to_col);
        }

        // Normal diagonal capture
        if (row_diff == 1 && abs_col_diff == 1)
        {
            char target = get_piece_at(board, to_row, to_col);

            // Regular capture
            if (is_black_piece(target))
            {
                return 1;
            }

            // EN PASSANT CHECK
            if (last_move != NULL && from_row == 4)
            { // White pawn must be on row 4
                // Check if last move was a black pawn moving 2 squares forward
                char last_piece = tolower(last_move->piece_moved);
                int last_from = last_move->from_row;
                int last_to = last_move->to_row;
                int last_col = last_move->to_col;

                // Conditions for en passant:
                // 1. Last move was a pawn ('P' for black)
                // 2. Moved from row 6 to row 4 (2 squares)
                // 3. Landed next to our pawn (same row, adjacent column)
                if (last_piece == 'p' &&
                    last_from == 6 && last_to == 4 &&
                    last_to == from_row &&
                    last_col == to_col)
                {
                    return 1; // Valid en passant
                }
            }
        }

        return 0;
    }

    // BLACK PAWN
    else
    {
        if (row_diff >= 0)
            return 0;

        // Normal forward move
        if (row_diff == -1 && col_diff == 0)
        {
            return is_square_empty(board, to_row, to_col);
        }

        // First move: 2 squares
        if (row_diff == -2 && col_diff == 0 && from_row == 6)
        {
            return is_square_empty(board, to_row, to_col) && is_path_clear(board, from_row, from_col, to_row, to_col);
        }

        // Normal diagonal capture
        if (row_diff == -1 && abs_col_diff == 1)
        {
            char target = get_piece_at(board, to_row, to_col);

            // Regular capture
            if (is_white_piece(target))
            {
                return 1;
            }

            // EN PASSANT CHECK
            if (last_move != NULL && from_row == 3)
            { // Black pawn must be on row 3
                // Check if last move was a white pawn moving 2 squares forward
                char last_piece = tolower(last_move->piece_moved);
                int last_from = last_move->from_row;
                int last_to = last_move->to_row;
                int last_col = last_move->to_col;

                // Conditions for en passant:
                // 1. Last move was a pawn ('p' for white)
                // 2. Moved from row 1 to row 3 (2 squares)
                // 3. Landed next to our pawn (same row, adjacent column)
                if (last_piece == 'p' &&
                    last_from == 1 && last_to == 3 &&
                    last_to == from_row &&
                    last_col == to_col)
                {
                    return 1; // Valid en passant
                }
            }
        }

        return 0;
    }
}
// main move validation will check on general on any move and that is the one will be used
int is_valid_move(char board[8][8], int from_row, int from_col, int to_row, int to_col, int is_white_turn, LastMove *last_move)
{
    if (from_row < 0 || from_row > 7 || from_col < 0 || from_col > 7 ||
        to_row < 0 || to_row > 7 || to_col < 0 || to_col > 7)
    {
        return 0; // out of bounds
    }
    char piece = get_piece_at(board, from_row, from_col);
    char desired_place = get_piece_at(board, to_row, to_col);
    if (is_square_empty(board, from_row, from_col))
    {
        return 0; // no piece to move
    }
    if (!is_square_empty(board, to_row, to_col))
    {
        if (is_white_piece(desired_place) && is_white_turn) // teammate on the desired square
        {
            return 0;
        }
        if (!is_white_piece(desired_place) && !is_white_turn) // teammate on the desired square
        {
            return 0;
        }
    }
    if (is_square_empty(board, from_row, from_col))
    {
        return 0; // No piece to move
    }

    // check if it's the correct player's piece
    if (is_white_turn && !is_white_piece(piece))
    {
        return 0; // not white's piece
    }
    if (!is_white_turn && !is_black_piece(piece))
    {
        return 0; // not black's piece
    }
    char piece_type = tolower(piece);
    switch (piece_type)
    {
    case 'r':
        return is_valid_rook_move(board, from_row, from_col, to_row, to_col);
        break;
    case 'b':
        return is_valid_bishop_move(board, from_row, from_col, to_row, to_col);
        break;
    case 'q':
        return is_valid_queen_move(board, from_row, from_col, to_row, to_col);
        break;
    case 'k':
        return is_valid_king_move(from_row, from_col, to_row, to_col);
        break;
    case 'n':
        return is_valid_knight_move(from_row, from_col, to_row, to_col);
        break;
    case 'p':
        return is_valid_pawn_move(board, from_row, from_col, to_row, to_col, is_white_turn, last_move);
        break;
    default:
        return 0;
    }
}