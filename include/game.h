#ifndef GAME_H
#define GAME_H
#include "types.h"
/*
 * GAME MODULE
 *
 * RESPONSIBLE FOR: Game state, check/checkmate/stalemate detection
 *
 * TASKS:
 * - Detect if a king is in check
 * - Detect if a king is in checkmate
 * - Detect if the game is in stalemate
 * - Handle pawn promotion
 * - Track whose turn it is
 * - Track game status (ongoing, checkmate, stalemate, draw)
 *
 * NOTES:
 * - Check = king is under attack
 * - Checkmate = king is in check AND no legal moves to escape
 * - Stalemate = no legal moves available BUT king is NOT in check
 * - This is the HARDEST part of the project!
 */

int find_king(char board[8][8], int *king_row, int *king_col, int is_white_king);
// Check if the king of a specific color is in check
int is_king_in_check(char board[8][8], int is_white_king);

// Check if the king of a specific color is in checkmate
int is_checkmate(char board[8][8], int is_white_king);

// Check if the game is in stalemate
int is_stalemate(char board[8][8], int is_white_turn);

// Handle pawn promotion (when pawn reaches opposite end)
void promote_pawn(char board[8][8], int to_row, int to_col, int from_row, int from_col, char new_piece);

// Check if a pawn is eligible for promotion
int can_promote(char board[8][8], int row, int col);

int has_legal_moves(char board[8][8], int is_white_turn);

// Position hashing and repetition detection
void create_position_hash(game_state *Gs, position_hash *hash);
int positions_equal(position_hash *pos1, position_hash *pos2);
int count_position_repetitions(game_state *Gs);
int is_draw_by_repetition(game_state *Gs);
void record_position(game_state *Gs);

// draw by insufficient material
int is_draw_by_insufficient_material(char board[8][8]);
#endif