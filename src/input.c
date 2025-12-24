#include "../include/input.h"
#include "../include/file_io.h"
#include "../include/board.h"
#include "../include/game.h"
#include "../include/display.h"
#include "../include/history.h"
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
// scanning inputs and printing Errors
void input_handling(char *from_col_char, char *to_col_char, char *from_row_char, char *to_row_char, char board[8][8], char captured_pieces[2][16], int *is_white_turn, int *is_black_turn, int *game_count, int *undo_flag, int *white_capture_count, int *black_capture_count, char captured_piece)

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
                            printf("\033[2J\033[H"); // cleaning terminal
                            display_board(board);
                            display_turn(*is_white_turn);
                        }
                        else // if returns an error
                        {
                            printf("Error loading the game!\n");
                        }
                    }
                    else
                    {
                        if ((c[0] == 'U') && (c[1] == 'N') && (c[2] == 'D') && (c[3] == 'O'))
                        {
                            *game_count -= 1;
                            if (captured_piece != '-' && captured_piece != '.')
                            {
                                if (is_white_piece(captured_piece))
                                {
                                    (*black_capture_count)--;
                                }
                                else if (is_black_piece(captured_piece))
                                {
                                    (*white_capture_count)--;
                                }
                            }
                            if (undo_game(board, captured_pieces, is_white_turn, *game_count) == 0)
                            {
                                printf("Undo GAME\n");
                                *undo_flag += 1;

                                printf("\033[2J\033[H"); // cleaning terminal
                                display_board(board);
                                display_captured_pieces(captured_pieces, *white_capture_count, *black_capture_count);
                                display_turn(*is_white_turn);
                            }
                            else
                            {
                                printf("Unsuccessful Undo!\n");
                            }
                        }
                        else
                        {
                            if ((c[0] == 'R') && (c[1] == 'E') && (c[2] == 'D') && (c[3] == 'O'))
                            {
                                if (*undo_flag)
                                {
                                    *game_count += 1;
                                    if (captured_piece != '-' && captured_piece != '.')
                                    {
                                        if (is_white_piece(captured_piece))
                                        {
                                            (*black_capture_count)++;
                                        }
                                        else if (is_black_piece(captured_piece))
                                        {
                                            (*white_capture_count)++;
                                        }
                                    }
                                    if (undo_game(board, captured_pieces, is_white_turn, *game_count) == 0)
                                    {
                                        printf("Redo GAME\n");
                                        *undo_flag -= 1;
                                        printf("\033[2J\033[H"); // cleaning terminal
                                        display_board(board);
                                        display_captured_pieces(captured_pieces, *white_capture_count, *black_capture_count);
                                        display_turn(*is_white_turn);
                                    }

                                    else
                                    {
                                        printf("Unsuccessful Redo!\n");
                                    }
                                }
                                else
                                {
                                    printf("No  possible redo!\n");
                                }
                            }

                            else
                            {
                                // DRAW user input handling
                                if ((c[0] == 'D') && (c[1] == 'R') && (c[2] == 'A') && (c[3] == 'W'))
                                {
                                    printf("%s offers a draw.\n", *is_white_turn ? "White" : "Black");
                                    printf("%s, do you accept the draw? (y/n): ", *is_white_turn ? "Black" : "White");

                                    char response;
                                    for (int i = 0; i < 1; i++)
                                    {
                                        scanf("%c", &response);
                                        if ((response == ' ') || (response == '\n') || (response == '\t'))
                                        {
                                            i--;
                                        }
                                    }
                                    while (getchar() != '\n')
                                        ;

                                    if (response == 'y' || response == 'Y')
                                    {
                                        printf("###################################\n");
                                        printf("#                                 #\n");
                                        printf("#         Draw Accepted           #\n");
                                        printf("#             Draw🤝              #\n");
                                        printf("#                                 #\n");
                                        printf("###################################\n");
                                        exit(0); // Exit game
                                    }
                                    else
                                    {
                                        printf("Draw offer declined. Continue playing.\n");
                                    }
                                }
                                else
                                {
                                    // RESIGN user input handling
                                    if ((c[0] == 'R') && (c[1] == 'E') && (c[2] == 'S') && (c[3] == 'I'))
                                    {
                                        printf("###################################\n");
                                        printf("#            RESIGNED              #\n");
                                        printf("#                                 #\n");
                                        *is_white_turn ? printf("#            Black Won            #\n") : printf("#            White Won            #\n");
                                        printf("###################################\n");
                                        exit(0); // Exit game
                                    }
                                    else // if an invalid user input
                                    {
                                        printf("ERROR!!..Enter move (e.g E2E4) or command (save/load/undo/redo/draw/resign/quit):\n");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// valid promotion  character
int valid_promoted_char(char *c)
{
    *c = tolower(*c);
    return (((*c == 'r') || (*c == 'n') || (*c == 'b') || (*c == 'q')));
}

// checking if pawn will promote
int will_promote(char board[8][8], int *to_row, int *from_row, int *from_col)
{
    char piece = board[*from_row][*from_col];
    if (piece == 'p' && *to_row == 7)
    {
        return 1;
    }
    if (piece == 'P' && *to_row == 0)
    {
        return 1;
    }
    return 0;
}

// additional input if pawn can promoted
void promotion_input(char board[8][8], int *to_row, int *from_row, int *from_col, char *promoted_to)
{
    int Error_flag = 1;
    while (Error_flag)
    {
        if (will_promote(board, to_row, from_row, from_col))
        {
            printf("Enter the piece you want to promote to\n");
            for (int i = 0; i < 1; i++)
            {
                scanf("%c", promoted_to);
                if ((*promoted_to == ' ') || (*promoted_to == '\n') || (*promoted_to == '\t'))
                {
                    i--;
                }
            }
            // cleaning buffer from extra length user input
            while ((getchar()) != '\n')
                ;
            if (valid_promoted_char(promoted_to))
            {
                Error_flag = 0;
            }
            else
            {
                printf("Error enter a valid character to promote to,Must be Q, R, B, or N\n");
            }
        }
        else
        {
            Error_flag = 0;
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