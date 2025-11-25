#include "../include/board.h"
#include <stdio.h>
#include <ctype.h>

char get_piece_at(char board[8][8], int row, int col)
{
    if (row > 7 || row < 0 || col > 7 || col < 0) // checking to avoid crashing
    {
        return '\0'; // invalid position not on board
    }
    else
    {
        return board[row][col];
    }
}

int is_square_empty(char board[8][8], int row, int col)
{
    char piece = get_piece_at(board, row, col); // getting the piece first
    return ((piece == '-') || (piece == '.'));  // checking if it is a white or black square with no pieces on
}

int is_white_piece(char piece)
{
    return ((piece >= 'a') && (piece <= 'z')); // white pieces are small alphabet so we checking based on ASCII
}

int is_black_piece(char piece)
{
    return ((piece >= 'A') && (piece <= 'Z')); // same black pieces are Capital alphabet so we checking based on ASCII
}

void make_move(char board[8][8], int from_row, int from_col, int to_row, int to_col)
{
    char piece = board[from_row][from_col]; // first getting the piece
    board[to_row][to_col] = piece;          // adding it to the desired square
    if ((from_row + from_col) % 2 == 0)     // checking if the square we moved from should be white or black
    {
        board[from_row][from_col] = '-';
    }
    else
    {
        board[from_row][from_col] = '.';
    }
}