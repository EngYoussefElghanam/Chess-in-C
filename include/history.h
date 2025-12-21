#ifndef HISTORY_H
#define HISTORY_H

/*
 * HISTORY MODULE
 *
 * RESPONSIBLE FOR: Undo and redo functionality
 *
 * TASKS:
 * - Store move history in an array
 * - Add new moves to history
 * - Undo last move (restore previous board state)
 * - Redo a move that was undone
 * - Keep track of current position in history
 * - Clear redo history when a new move is made after undo
 *
 * NOTES:
 * - Think of it like a stack or array
 * - Need to save: from position, to position, piece moved, piece captured
 * - Undo goes backward in history, redo goes forward
 * - Max moves = probably 500 should be enough
 */

// save game state for each turn
int save_game_state(char board[8][8], char captured_pieces[2][16], int *is_white_turn);

// undo game
int undo_game(char board[8][8], char captured_pieces[2][16], int *is_white_turn, int game_count);

// correction saving without previous undo game state
int saving_correction(int count);
#endif