#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/input.h"
#include "../include/file_io.h"
#include "../include/moves.h"
#include "../include/game.h"
#include "../include/board.h"
#include "../include/display.h"

// save game function for board,captured pieces and current turn
int save_game(char *file_name, char board[8][8], char captured_pieces[2][16], int *is_white_turn)
{
    char dest[100] = "saves/";
    strcat(dest, file_name);
    FILE *file = fopen(dest, "w");
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

                fprintf(file, "%c", captured_pieces[i][j]); // printing the captured pieces to the file
            }
        }

        fprintf(file, "%d", *is_white_turn); // printing the turn to the file

        fclose(file);
        return 0; // successful saving
    }
}

// load game functuion for all previous loading
int load_game(char *file_name, char board[8][8], char captured_pieces[2][16], int *is_white_turn)
{
    char dest[100] = "saves/";
    strcat(dest, file_name);
    FILE *file = fopen(dest, "r");
    if (file == NULL)
    {
        return -1; // error
    }
    else
    {
        fseek(file, 0, 0);

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {

                fscanf(file, "%c", &board[i][j]); // reading the board
            }
        }
        fseek(file, SEEK_CUR, 64); // changing the pointer in the file
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 16; j++)
            {

                fscanf(file, "%c", &captured_pieces[i][j]); // reading captured_pieces array
            }
        }
        fseek(file, SEEK_CUR, 32);         // changing the pointer in the file
        fscanf(file, "%d", is_white_turn); // reading the current turn
    }
    fclose(file);
    return 0; // successful loading
}