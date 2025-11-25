#ifndef DISPLAY_H
#define DISPLAY_H

/*
 * DISPLAY MODULE
 *
 * RESPONSIBLE FOR: Showing the game to the user in a nice format
 *
 * TASKS:
 * - Display the 8x8 board with pieces
 * - Show column labels (A-H) above and below board
 * - Show row numbers (1-8) on left and right of board
 * - Display captured pieces for white
 * - Display captured pieces for black
 * - Display game status messages (check, checkmate, stalemate)
 * - Display whose turn it is
 *
 * NOTES:
 * - Make it look nice and easy to read!
 * - Use printf statements
 * - Example output should look like the project PDF description
 */

// Display the board with coordinates (A-H, 1-8)
void display_board(char board[8][8]);

// Display captured pieces for both players
void display_captured_pieces(char white_captured[], int white_count,
                             char black_captured[], int black_count);

// Display whose turn it is
void display_turn(int is_white_turn);

// Display a message (check, checkmate, invalid move, etc.)
void display_message(char *message);

// Clear the screen (optional, for better user experience)
void clear_screen();

// Display the full game state (board + captured pieces + turn)
void display_game(char board[8][8], char white_captured[], int white_count,
                  char black_captured[], int black_count, int is_white_turn);

#endif