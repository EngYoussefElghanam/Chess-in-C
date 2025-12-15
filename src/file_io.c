#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/input.h"
#include "../include/file_io.h"
#include "../include/moves.h"
#include "../include/game.h"
#include "../include/board.h"
#include "../include/display.h"

// save board
int save_board(char *file_name_input, char board[8][8])
{
    // file name suffix
    strcat(file_name_input, "_board.txt");

    // open the file to write
    FILE *file_board = fopen(file_name_input, "w");
    if (file_board == NULL)
    {
        return -1; // error
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {

                fprintf(file_board, "%c", board[i][j]); // printing the board to the file
            }
        }
        fclose(file_board);
        return 0; // successful saving
    }
}

// save captured pieces array
int save_captured(char *file_name_input, char captured_pieces[2][16])
{
    // file name suffix
    strcat(file_name_input, "_captured.txt");

    // open the file to write
    FILE *file_captured = fopen(file_name_input, "w");
    if (file_captured == NULL)
    {
        return -1; // error
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 16; j++)
            {

                fprintf(file_captured, "%c", captured_pieces[i][j]); //// printing the captured pieces to the file
            }
        }
        fclose(file_captured);
        return 0; // successful saving
    }
}

// save the current turn
int save_turn(char *file_name_input, int *is_white_turn)
{
    // file name suffix
    strcat(file_name_input, "_turn.txt");

    // open the file to write
    FILE *file_turn = fopen(file_name_input, "w");
    if (file_turn == NULL)
    {
        return -1; // error
    }
    else
    {

        fprintf(file_turn, "%d", *is_white_turn); // printing the turn to the file
    }

    fclose(file_turn);
    return 0;
}

// save game function for all previous saving
int save_game(char *file_name, char board[8][8], char captured_pieces[2][16], int *is_white_turn)
{
    int save_board_flag, save_captured_flag, save_turn_flag;
    int save_game_flag;
    char file_name_cpy1[100];
    strcpy(file_name_cpy1, file_name); // copying the file name user input for different suffix files names

    char file_name_cpy2[100];
    strcpy(file_name_cpy2, file_name);

    // flags to determine successful or failed saving
    save_board_flag = save_board(file_name, board);
    save_captured_flag = save_captured(file_name_cpy1, captured_pieces);
    save_turn_flag = save_turn(file_name_cpy2, is_white_turn);

    if ((save_board_flag == 0) && (save_captured_flag == 0) && (save_captured_flag == 0))
    {
        save_game_flag = 0;
    }
    else
    {
        save_game_flag = -1;
    }

    return save_game_flag;
}

// loading board
int load_board(char *file_name_input, char board[8][8])
{
    // file name suffix
    strcat(file_name_input, "_board.txt");

    // openeing the file to read
    FILE *file_board = fopen(file_name_input, "r");
    if (file_board == NULL)
    {
        return -1; // error
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {

                fscanf(file_board, "%c", &board[i][j]); // reading the board
            }
        }
        fclose(file_board);
        return 0; // successful loading
    }
}

int load_captured(char *file_name_input, char captured_pieces[2][16])
{
    // file name suffix
    strcat(file_name_input, "_captured.txt");

    // openeing the file to read
    FILE *file_captured = fopen(file_name_input, "r");
    if (file_captured == NULL)
    {
        return -1; // error
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 16; j++)
            {

                fscanf(file_captured, "%c", &captured_pieces[i][j]); // reading captured_pieces array
            }
        }
        fclose(file_captured);
        return 0; // successful loading
    }
}

int load_turn(char *file_name_input, int *is_white_turn)
{
    // file name suffix
    strcat(file_name_input, "_turn.txt");

    // openeing the file to read
    FILE *file_turn = fopen(file_name_input, "r");
    if (file_turn == NULL)
    {
        return -1; // error
    }
    else
    {

        fscanf(file_turn, "%d", is_white_turn); // reading the current turn
    }

    fclose(file_turn);
    return 0; // successful loading
}

// load game functuion for all previous loading
int load_game(char *file_name, char board[8][8], char captured_pieces[2][16], int *is_white_turn)
{
    int load_board_flag, load_captured_flag, load_turn_flag;
    int load_game_flag;

    // copying the file name user input for different suffix files names
    char file_name_cpy1[100];
    strcpy(file_name_cpy1, file_name);

    char file_name_cpy2[100];
    strcpy(file_name_cpy2, file_name);

    // flags to determine successful or failed saving
    load_board_flag = load_board(file_name, board);
    load_captured_flag = load_captured(file_name_cpy1, captured_pieces);
    load_turn_flag = load_turn(file_name_cpy2, is_white_turn);

    if ((load_board_flag == 0) && (load_captured_flag == 0) && (load_captured_flag == 0))
    {
        load_game_flag = 0;
    }
    else
    {
        load_game_flag = -1;
    }

    return load_game_flag;
}