#ifndef INPUT_H
#define INPUT_H

/*
 * INPUT MODULE
 *
 * RESPONSIBLE FOR: Getting input from user and converting it to coordinates
 *
 * TASKS:
 * - Read move from user (e.g., "A3B4" or "H7H8Q" for promotion)
 * - Parse the input string into row and column numbers
 * - Validate input format (correct length, valid characters)
 * - Convert 'A'-'H' to column numbers 0-7
 * - Convert '1'-'8' to row numbers 0-7
 * - Handle promotion moves (extra character at end)
 *
 * NOTES:
 * - User enters like: "E2E4" to move from E2 to E4
 * - A=0, B=1, C=2, D=3, E=4, F=5, G=6, H=7
 * - 1=0, 2=1, 3=2, 4=3, 5=4, 6=5, 7=6, 8=7
 * - Must validate that input is correct format!
 */

// checking character index validation
int valid_col(char *c);

// checking row number index validation.
int valid_row(char *n);

// handling inputs and printing Errors
void input_handling(char *from_col_char, char *to_col_char, char *from_row_char, char *to_row_char, char board[8][8], char captured_pieces[2][16], int *is_white_turn, int *is_black_turn);

// convert from (A to H)index to(0 to 7)index
void convert_col_index(char *from_col_char, char *to_col_char, int *from_col, int *to_col);

// convert from(1 to 8)index to (0 to 7)index
void convert_row_index(char *from_row_char, char *to_row_char, int *from_row, int *to_row);

// valid promotion  character
int valid_promoted_char(char *c);

// checking if pawn will promote
int will_promote(char board[8][8], int *to_row, int *current_col);

// addtional input if can promoted
void promotion_input(char board[8][8], int *to_row, int *from_col, char *promoted_to);
#endif