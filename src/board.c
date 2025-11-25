#include "../include/board.h"
#include <stdio.h>
#include <ctype.h>

void initialize_board(char board[8][8])
{
    board[7][0] = 'R';
    board[7][1] = 'N';
    board[7][2] = 'B';
    board[7][3] = 'Q';
    board[7][4] = 'K';
    board[7][5] = 'B';
    board[7][6] = 'N';
    board[7][7] = 'R';

    for (int i = 0; i < 8; i++)
    {
        board[6][i] = 'P'; // Black pawns on row 6
    }

    // Set up empty squares with checkerboard pattern
    for (int row = 2; row < 6; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if ((row + col) % 2 == 0)
            {
                board[row][col] = '-'; // White square
            }
            else
            {
                board[row][col] = '.'; // Black square
            }
        }
    }

    // Set up white pieces
    for (int i = 0; i < 8; i++)
    {
        board[1][i] = 'p'; // White pawns on row 1
    }
    board[0][0] = 'r';
    board[0][1] = 'n';
    board[0][2] = 'b';
    board[0][3] = 'q';
    board[0][4] = 'k';
    board[0][5] = 'b';
    board[0][6] = 'n';
    board[0][7] = 'r';
}

void print_board_simple(char board[8][8])
{
    for (int row = 7; row >= 0; row--)
    { // Print from top to bottom
        for (int col = 0; col < 8; col++)
        {
            printf("%c ", board[row][col]);
        }
        printf("\n");
    }
}

char get_piece_at(char board[8][8], int row, int col)
{
    if (row > 7 || row < 0 || col > 7 || col < 0) // checking to avoid crashing
    {
        return '\0';
    }
    else
    {
        return board[row][col];
    }
}

int is_square_empty(char board[8][8], int row, int col)
{
    char piece = get_piece_at(board, row, col); // getting piece first
    return ((piece == '-') || (piece == '.'));
}

int is_white_piece(char piece)
{
    return ((piece >= 'a') && (piece <= 'z')); // white pieces are small alphabet so will take advantage of ascii
}

int is_black_piece(char piece)
{
    return ((piece >= 'A') && (piece <= 'Z')); // same here take advantage of ascii
}

void make_move(char board[8][8], int from_row, int from_col, int to_row, int to_col)
{
    char piece = board[from_row][from_col]; // getting the piece desired to get moved
    board[to_row][to_col] = piece;          // moving it to the desired place
    if ((from_row + from_col) % 2 == 0)     // checking if it is white or black
    {
        board[from_row][from_col] = '-'; // white
    }
    else
    {
        board[from_row][from_col] = '.'; // black
    }
}