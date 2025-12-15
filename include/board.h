#ifndef BOARD_H
#define BOARD_H

/*
 * BOARD MODULE
 *
 * RESPONSIBLE FOR: Core board data structure and basic board operations
 *
 * TASKS:
 * - Initialize the board to starting chess position
 * - Represent pieces: lowercase = white (p,r,n,b,q,k), uppercase = black (P,R,N,B,Q,K)
 * - Represent empty squares: '.' = black square, '-' = white square
 * - Make moves on the board (update board array)
 * - Get piece at a specific position
 * - Check if a square is empty
 * - Check if a piece belongs to a player
 *
 * NOTES:
 * - Board is 8x8 array: board[row][col]
 * - Row 0 = white's back rank, Row 7 = black's back rank
 * - Col 0 = column A, Col 7 = column H
 */

// Initialize the board to starting chess position
void initialize_board(char board[8][8]);

// Make a move on the board (updates the board array)
void make_move(char board[8][8], int from_row, int from_col, int to_row, int to_col);
char execute_move(char board[8][8], int from_row, int from_col, int to_row, int to_col);

// Get the piece at a specific position
char get_piece_at(char board[8][8], int row, int col);

// Check if a square is empty (returns 1 if empty, 0 if occupied)
int is_square_empty(char board[8][8], int row, int col);

// Check if a piece belongs to white (returns 1 if white, 0 if not)
int is_white_piece(char piece);

// Check if a piece belongs to black (returns 1 if black, 0 if not)
int is_black_piece(char piece);

// Temporary function for testing - prints board without formatting
void print_board_simple(char board[8][8]);

#endif