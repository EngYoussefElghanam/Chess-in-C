#ifndef MOVES_H
#define MOVES_H
#include "types.h"
/*
 * MOVES MODULE
 *
 * RESPONSIBLE FOR: Validating if moves are legal according to chess rules
 *
 * TASKS:
 * - Validate pawn moves (including en passant if bonus)
 * - Validate rook moves (straight lines)
 * - Validate knight moves (L-shape)
 * - Validate bishop moves (diagonals)
 * - Validate queen moves (rook + bishop)
 * - Validate king moves (one square in any direction, castling if bonus)
 * - Check if path is clear (no pieces blocking)
 * - Main validation function that calls specific piece validators
 *
 * NOTES:
 * - Must check: piece movement rules, not jumping over pieces, not capturing own pieces
 * - Must prevent moves that leave own king in check
 * - Read chess rules carefully from Wikipedia link in project PDF
 */

// Main move validation function - returns 1 if valid, 0 if invalid
int is_valid_move(game_state *Gs, int from_row, int from_col, int to_row, int to_col);

// Validate pawn movement
int is_valid_pawn_move(char board[8][8], int from_row, int from_col, int to_row, int to_col, int is_white, last_move *last_move);

// Validate rook movement (straight lines)
int is_valid_rook_move(char board[8][8], int from_row, int from_col, int to_row, int to_col);

// Validate knight movement (L-shape)
int is_valid_knight_move(int from_row, int from_col, int to_row, int to_col);

// Validate bishop movement (diagonals)
int is_valid_bishop_move(char board[8][8], int from_row, int from_col, int to_row, int to_col);

// Validate queen movement (rook + bishop combined)
int is_valid_queen_move(char board[8][8], int from_row, int from_col, int to_row, int to_col);

// Validate king movement (one square any direction)
int is_valid_king_move(int from_row, int from_col, int to_row, int to_col);

// Check if path between two squares is clear (for rook, bishop, queen)
int is_path_clear(char board[8][8], int from_row, int from_col, int to_row, int to_col);

// making one with no check so no stackoverflow happens
int is_valid_move_no_check(game_state *Gs, int from_row, int from_col, int to_row, int to_col);
int is_square_attacked(char board[8][8], int row, int col, int by_white);

int is_path_attacked(char board[8][8], int from_row, int from_col, int to_col, int is_white);
int is_valid_castling(game_state *Gs, int from_row, int from_col, int to_row, int to_col);

#endif