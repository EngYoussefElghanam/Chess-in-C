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

// Structure to hold a parsed move
typedef struct
{
    int from_row;
    int from_col;
    int to_row;
    int to_col;
    char promotion_piece; // '\0' if not a promotion move
    int is_valid_format;  // 1 if format is correct, 0 if invalid
} ParsedMove;

// Get input from user (reads a line from stdin)
void get_user_input(char *buffer, int max_length);

// Parse move string (e.g., "A3B4") into row/column numbers
ParsedMove parse_move(char *input);

// Validate that input format is correct (A-H for columns, 1-8 for rows)
int validate_input_format(char *input);

// Convert column letter to number (A->0, B->1, ... H->7)
int column_to_index(char column);

// Convert row number to index (1->0, 2->1, ... 8->7)
int row_to_index(char row);

// scanning inputs and printing Errors
void input_validation(char *from_char, char *to_char, int *from_row, int *to_row);

#endif