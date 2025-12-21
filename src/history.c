#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/input.h"
#include "../include/file_io.h"
#include "../include/moves.h"
#include "../include/game.h"
#include "../include/board.h"
#include "../include/history.h"

// save game state for each turn
int save_game_state(char board[8][8], char captured_pieces[2][16], int *is_white_turn)
{
    FILE *file = fopen("^&@!~`'.txt", "a");
    if (file == NULL)
    {
        return -1; // error
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {

                fprintf(file, "%c", board[i][j]); // printing the board to the file
            }
        }

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 16; j++)
            {

                fprintf(file, "%c", captured_pieces[i][j]); //// printing the captured pieces to the file
            }
        }

        fprintf(file, "%d", *is_white_turn); // printing the turn to the file

        fclose(file);
        return 0; // successful saving
    }
}

// undo game
int undo_game(char board[8][8], char captured_pieces[2][16], int *is_white_turn, int game_count)
{
    FILE *file = fopen("^&@!~`'.txt", "r");
    if (file == NULL)
    {
        return -1; // error
    }
    else
    {
        fseek(file, 97 * game_count, 0);

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {

                fscanf(file, "%c", &board[i][j]); // reading the board
            }
        }
        fseek(file, 0, SEEK_CUR); // changing the pointer in the file
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 16; j++)
            {

                fscanf(file, "%c", &captured_pieces[i][j]); // reading captured_pieces array
            }
        }
        fseek(file, 0, SEEK_CUR);          // changing the pointer in the file
        fscanf(file, "%d", is_white_turn); // reading the current turn
    }
    fclose(file);
    return 0; // successful loading
}

int saving_correction(int count)
{
    // a temporary file to save game state without any previous undo state
    FILE *file_tmp = fopen("^&@!~`'_tmp.txt", "w");
    FILE *file = fopen("^&@!~`'.txt", "r");
    if (file == NULL || file_tmp == NULL)
    {
        return -1; // error
    }
    else
    {

        char c[count * 97]; // 97 is total chars number of board,captured pieces,turn
        for (int i = 0; i < count * 97; i++)
        {
            fscanf(file, "%c", &c[i]);
        } // printing the board to the fil
        for (int i = 0; i < count * 97; i++)
        {
            fprintf(file_tmp, "%c", c[i]);
        }

        fclose(file);
        fclose(file_tmp);
        remove("^&@!~`'.txt");                    // deleting the old file
        rename("^&@!~`'_tmp.txt", "^&@!~`'.txt"); // renaming the temporary to the old file name

        return 0; // successful saving
    }
}