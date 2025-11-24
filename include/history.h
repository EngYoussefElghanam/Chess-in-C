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

#define MAX_HISTORY 500

// Structure to store one move
typedef struct
{
    int from_row;
    int from_col;
    int to_row;
    int to_col;
    char piece_moved;
    char piece_captured; // '\0' if no piece was captured
} MoveHistory;

// Global history array and counters (or you can pass them as parameters)
extern MoveHistory history[MAX_HISTORY];
extern int history_count;    // Number of moves in history
extern int current_position; // Current position in history (for redo)

// Add a move to history
void add_move_to_history(int from_row, int from_col, int to_row, int to_col,
                         char piece_moved, char piece_captured);

// Undo the last move (returns 1 if successful, 0 if nothing to undo)
int undo_move(char board[8][8]);

// Redo a move that was undone (returns 1 if successful, 0 if nothing to redo)
int redo_move(char board[8][8]);

// Check if undo is possible
int can_undo();

// Check if redo is possible
int can_redo();

// Clear all history (for new game)
void clear_history();

#endif