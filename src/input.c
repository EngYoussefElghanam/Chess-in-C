#include "../include/input.h"
#include "../include/file_io.h"
#include "../include/board.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// checking character index validation
int valid_col(char *c)
{
    return (((*c >= 'A') && (*c <= 'H')) || ((*c >= 'a') && (*c <= 'h')));
}

// checking row number index validation.
int valid_row(char *n)
{
    return ((*n >= '1') && (*n <= '8'));
}

// scanning inputs and printing Errors
void input_handling(char *from_col_char, char *to_col_char, char *from_row_char, char *to_row_char, char board[8][8], char captured_pieces[2][16], int *is_white_turn, int *is_black_turn)

{

    int Error_flag = 1;
    while (Error_flag)
    {
        char c[4]; // from_char, from_row, to_char, to_row

        for (int i = 0; i < 4; i++)
        {
            scanf("%c", &c[i]);
            if ((c[i] == ' ') || (c[i] == '\n') || (c[i] == '\t'))
            {
                i--;
            }
        }

        // changing all to uppercase.
        for (int i = 0; i < 4; i++)
        {
            c[i] = toupper(c[i]);
        }

        *from_col_char = c[0];
        *from_row_char = c[1];
        *to_col_char = c[2];
        *to_row_char = c[3];

        // cleaning buffer from extra length user input
        while ((getchar()) != '\n')
            ;

        // checking input validation
        if (valid_col(from_col_char) && valid_col(to_col_char) && valid_row(from_row_char) && valid_row(to_row_char))
        {
            Error_flag = 0;
        }
        else
        {
            // QUIT user input handling
            if ((c[0] == 'Q') && (c[1] == 'U') && (c[2] == 'I') && (c[3] == 'T'))
            {
                printf("Game Quit\n");
                exit(1); // exit game
            }
            else
            {
                // SAVE user input handling
                if ((c[0] == 'S') && (c[1] == 'A') && (c[2] == 'V') && (c[3] == 'E'))
                {
                    // input a file name to be saved
                    printf("Enter the file name to save \n");
                    char file_name_input[100];
                    fgets(file_name_input, 100, stdin);
                    if (save_game(file_name_input, board, captured_pieces, is_white_turn) == 0) // successful game saving
                    {
                        printf("GAME SAVED\n");
                    }
                    else // if returns an error
                    {
                        printf("Error saving the game!\n");
                    }
                }
                else
                {
                    // LOAD user input handling
                    if ((c[0] == 'L') && (c[1] == 'O') && (c[2] == 'A') && (c[3] == 'D'))
                    {
                        // input saved file name to be loaded
                        printf("Enter the saved file name to be loaded \n");
                        char file_name_input[100];
                        fgets(file_name_input, 100, stdin);
                        if (load_game(file_name_input, board, captured_pieces, is_white_turn) == 0) // successful game loading
                        {
                            *is_black_turn = !*is_white_turn; // handling the current player turn
                            printf("GAME LOADED\n");
                        }
                        else // if returns an error
                        {
                            printf("Error loading the game!\n");
                        }
                    }

                    else // if an invalid user input
                    {
                        printf("ERROR!!..Enter move (e.g E2E4) or command (save/load/undo/redo/quit):\n");
                    }
                }
            }
        }
    }
}

// convert from (A to H)index to(0 to 7)index
void convert_col_index(char *from_col_char, char *to_col_char, int *from_col, int *to_col)
{

    *from_col = *from_col_char - 'A';
    *to_col = *to_col_char - 'A';
}

// convert from(1 to 8)index to (0 to 7)index
void convert_row_index(char *from_row_char, char *to_row_char, int *from_row, int *to_row)
{
    *from_row = *from_row_char - '1';
    *to_row = *to_row_char - '1';
}