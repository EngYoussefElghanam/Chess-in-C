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

    // Set up empty squares (rows 2-5) with checkerboard pattern
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

    // Set up white pieces (row 1 - pawns, row 0 - back rank)
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
    { // Print from top to bottom (row 7 to 0)
        for (int col = 0; col < 8; col++)
        {
            printf("%c ", board[row][col]);
        }
        printf("\n");
    }
}

char get_piece_at(char board[8][8], int row, int col)
{
    if (row > 7 || row < 0 || col > 7 || col < 0)
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
    char piece = get_piece_at(board, row, col);
    return ((piece == '-') || (piece == '.'));
}

int is_white_piece(char piece)
{
    return ((piece >= 'a') && (piece <= 'z'));
}

int is_black_piece(char piece)
{
    return ((piece >= 'A') && (piece <= 'Z'));
}

void make_move(char board[8][8], int from_row, int from_col, int to_row, int to_col)
{
    char piece = board[from_row][from_col];
    board[to_row][to_col] = piece;
    if ((from_row + from_col) % 2 == 0)
    {
        board[from_row][from_col] = '-';
    }
    else
    {
        board[from_row][from_col] = '.';
    }
}