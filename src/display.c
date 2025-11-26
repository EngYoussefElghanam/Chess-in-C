#include "../include/display.h"
#include <stdio.h>

void display_board(char board[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 0) // interchanging for white and black squares.
            {
                board[i][j] = '-'; //'-' for white squares.
            }
            else
            {
                board[i][j] = '.'; // '.' for black squares.
            }
        }
    }
    printf("\t");
    for (int i = 65; i <= 72; i++)
    {
        printf("%c  ", i); // ASCII code for A:65 to H:72 .
    }
    printf("\n");
    for (int i = 0; i < 8; i++)
    {

        printf("%d\t", 8 - i);

        for (int j = 0; j < 8; j++)
        {
            printf("%c  ", board[i][j]);
        }
        printf("\t%d\n", 8 - i);
    }
    printf("\t");
    for (int i = 65; i <= 72; i++)
    {
        printf("%c  ", i);
    }
    printf("\n"); // Tabs and newline spaces for better display.
}

void display_captured_pieces(char white_captured[], int white_count,
                             char black_captured[], int black_count)
{
    for (int i = 0; i < white_count; i++)
    {
        printf("White captured pieces:\n");

        printf("%c\t", white_captured[i]);
    }
    for (int j = 0; j < black_count; j++)
    {
        printf("Black captured pieces:\n");

        printf("%c\t", black_captured[j]);
    }
}

void display_turn(int is_white_turn)
{
    if (is_white_turn)
    {
        printf("This is White turn !\n");
    }
    else
    {
        printf("This is Black turn !\n");
    }
}
