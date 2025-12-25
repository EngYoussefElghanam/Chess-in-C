#include "../include/moves.h"
#include "../include/board.h"
#include "../include/game.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
// knight moves in L shape regardless of what is in the way
// except if there's a team-mate on the desired square this will be handled in the main move validation
int is_valid_knight_move(int from_row, int from_col, int to_row, int to_col)
{
    int row_diff = abs(to_row - from_row);
    int col_diff = abs(to_col - from_col);
    return ((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2)); // this ensures that it is L shaped move
}
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
int is_square_attacked(char board[8][8], int row, int col, int by_white)
{
    int king_row;
    int king_col;
    // getting king's row and column
    find_king(board, &king_row, &king_col, !by_white);
    // storing the king either it is white or black
    char king = board[king_row][king_col];
    // moving the king temporarily
    board[king_row][king_col] = (king_row + king_col) % 2 ? '-' : '.';
    char temp = board[row][col];
    board[row][col] = king;
    // checking after simulation
    int rtrnVal = is_king_in_check(board, !by_white);
    // restoring everything before returning
    board[row][col] = temp;
    board[king_row][king_col] = king;
    return rtrnVal;
}
int is_path_attacked(char board[8][8], int from_row, int from_col, int to_col, int is_white)
{
    int step = (to_col > from_col) ? 1 : -1;
    for (int c = from_col; c != to_col + step; c += step)
    {
        if (is_square_attacked(board, from_row, c, !is_white))
            return 1;
    }
    return 0;
}
int is_valid_castling(gameState *Gs, int from_row, int from_col, int to_row, int to_col)
{
    char piece = Gs->board[from_row][from_col];
    int is_white = Gs->is_white_turn;
    int col_diff = to_col - from_col;
    if (from_row != to_row)
    {
        return 0;
    }

    if (is_path_attacked(Gs->board, from_row, from_col, to_col, Gs->is_white_turn))
    {
        return 0;
    }
    if (abs(col_diff) != 2)
    {
        return 0;
    }
    if (tolower(piece) != 'k')
    {
        return 0;
    }
    if (is_king_in_check(Gs->board, Gs->is_white_turn))
    {
        return 0;
    }
    if (is_white)
    {
        if (Gs->white_king_moved)
        {
            return 0;
        }
        // king side castling
        if (col_diff == 2)
        {
            if (!is_path_clear(Gs->board, from_row, from_col, 0, 7))
            {
                return 0;
            }
            if (Gs->board[0][7] != 'r')
            {
                return 0;
            }
            if (Gs->white_rook_h_moved)
            {
                return 0;
            }
        }
        // Queen side castling
        else if (col_diff == -2)
        {
            if (!is_path_clear(Gs->board, from_row, from_col, 0, 0))
            {
                return 0;
            }
            if (Gs->board[0][0] != 'r')
            {
                return 0;
            }
            if (Gs->white_rook_a_moved)
            {
                return 0;
            }
        }
    }
    else if (!is_white)
    {
        if (Gs->black_king_moved)
        {
            return 0;
        }
        // king castling
        if (col_diff == 2)
        {
            if (!is_path_clear(Gs->board, from_row, from_col, 7, 7))
            {
                return 0;
            }
            if (Gs->board[7][7] != 'R')
            {
                return 0;
            }
            if (Gs->black_rook_h_moved)
            {
                return 0;
            }
        }
        else if (col_diff == -2)
        {
            if (!is_path_clear(Gs->board, from_row, from_col, 7, 0))
            {
                return 0;
            }
            if (Gs->board[7][0] != 'R')
            {
                return 0;
            }
            if (Gs->black_rook_a_moved)
            {
                return 0;
            }
        }
    }
    return 1;
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

int is_valid_move_no_check(gameState *Gs, int from_row, int from_col, int to_row, int to_col)
{
    // All your current validation EXCEPT the is_king_in_check part
    if (from_row < 0 || from_row > 7 || from_col < 0 || from_col > 7 ||
        to_row < 0 || to_row > 7 || to_col < 0 || to_col > 7)
    {
        return 0;
    }

    if (from_col == to_col && from_row == to_row)
    {
        return 0;
    }
    char board[8][8];
    memcpy(board, Gs->board, sizeof(board));
    int is_white_turn = Gs->is_white_turn;
    LastMove *last_move = Gs->last_move;
    char piece = get_piece_at(board, from_row, from_col);
    char desired_place = get_piece_at(board, to_row, to_col);

    if (is_square_empty(board, from_row, from_col))
    {
        return 0;
    }

    // Fixed teammate check
    if (!is_square_empty(board, to_row, to_col))
    {
        if (is_white_piece(desired_place) && is_white_turn)
        {
            return 0;
        }
        if (is_black_piece(desired_place) && !is_white_turn) //  Fixed
        {
            return 0;
        }
    }

    if (is_white_turn && !is_white_piece(piece))
    {
        return 0;
    }
    if (!is_white_turn && !is_black_piece(piece))
    {
        return 0;
    }

    // Validate piece-specific movement (NO check prevention here)
    char piece_type = tolower(piece);
    switch (piece_type)
    {
    case 'r':
        return is_valid_rook_move(board, from_row, from_col, to_row, to_col);
    case 'b':
        return is_valid_bishop_move(board, from_row, from_col, to_row, to_col);
    case 'q':
        return is_valid_queen_move(board, from_row, from_col, to_row, to_col);
    case 'k':
        return is_valid_king_move(from_row, from_col, to_row, to_col) || is_valid_castling(Gs, from_row, from_col, to_row, to_col);
    case 'n':
        return is_valid_knight_move(from_row, from_col, to_row, to_col);
    case 'p':
        return is_valid_pawn_move(board, from_row, from_col, to_row, to_col, is_white_turn, last_move);
    default:
        return 0;
    }
}

// Full validation WITH check prevention
int is_valid_move(gameState *Gs, int from_row, int from_col, int to_row, int to_col)
{
    // First check basic movement
    char (*board)[8] = Gs->board;
    int is_white_turn = Gs->is_white_turn;

    if (!is_valid_move_no_check(Gs, from_row, from_col, to_row, to_col))
    {
        return 0;
    }

    // Now check if move leaves king in check
    char from = board[from_row][from_col];
    char to = board[to_row][to_col];
    board[to_row][to_col] = from;
    board[from_row][from_col] = (from_row + from_col) % 2 == 0 ? '.' : '-';

    int is_check = is_king_in_check(board, is_white_turn);

    board[to_row][to_col] = to;
    board[from_row][from_col] = from;

    if (is_check)
    {
        return 0;
    }

    return 1;
}