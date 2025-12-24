#include "../include/board.h"
#include "../include/input.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

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

char execute_move(char board[8][8], int from_row, int from_col, int to_row, int to_col)
{
    char piece_moving = board[from_row][from_col];
    char captured_piece = board[to_row][to_col];
    if (tolower(piece_moving) == 'p' && is_square_empty(board, to_row, to_col) && abs(to_col - from_col) == 1)
    {
        captured_piece = board[from_row][to_col];
        if ((from_row + to_col) % 2 == 0)
        {
            board[from_row][to_col] = '-'; // white
        }
        else
        {
            board[from_row][to_col] = '.'; // black
        }
    }
    if (tolower(piece_moving) == 'k' && abs(from_col - to_col) == 2)
    {
        int col_diff = to_col - from_col;
        if (is_white_piece(piece_moving))
        {
            // king side Castling
            if (col_diff == 2)
            {
                board[0][to_col] = piece_moving;
                board[0][to_col - 1] = 'r';
                board[0][7] = '-';
                board[0][from_col] = '.';
            }
            // queen side Castling
            else if (col_diff == -2)
            {
                board[0][to_col] = piece_moving;
                board[0][to_col + 1] = 'r';
                board[0][0] = '.';
                board[0][from_col] = '.';
            }
        }
        else if (!is_white_piece(piece_moving))
        {
            // king side Castling
            if (col_diff == 2)
            {
                board[7][to_col] = piece_moving;
                board[7][to_col - 1] = 'R';
                board[7][7] = '.';
                board[7][from_col] = '-';
            }
            // queen side Castling
            else if (col_diff == -2)
            {
                board[7][to_col] = piece_moving;
                board[7][to_col + 1] = 'R';
                board[7][0] = '-';
                board[7][from_col] = '-';
            }
        }
    }
    else
    {
        make_move(board, from_row, from_col, to_row, to_col);
    }
    return captured_piece;
}