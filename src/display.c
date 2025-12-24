#include "../include/display.h"
#include <stdio.h>

void display_board(char board[8][8])
{

    // (A to H) for column indexing and (1 to 8) for row indexing displaying.
    printf("\t");
    for (char i = 'A'; i <= 'H'; i++)
    {
        printf("%c  ", i); // ASCII code for A:65 to H:72 .
    }
    printf("\n");
    printf("\n");

    for (char i = 7; i >= 0; i--)
    { // Print from top to bottom

        printf("%d\t", i + 1);

        for (int j = 0; j < 8; j++)
        {
            printf("%c  ", board[i][j]);
        }
        printf("\t%d\n", i + 1);
    }
    printf("\n");

    printf("\t");
    for (char i = 'A'; i <= 'H'; i++)
    {
        printf("%c  ", i);
    }

    printf("\n"); // Tabs and newline spaces for better display.
}

void display_captured_pieces(char captured_pieces[2][16], int white_count, int black_count)

{
    if (white_count > 0)
    {
        printf("White captured pieces:\n");
    }
    for (int i = 0; i < white_count; i++)
    {
        printf("%c\t", captured_pieces[1][i]);
    }
    printf("\n");
    if (black_count > 0)
    {
        printf("Black captured pieces:\n");
    }
    for (int j = 0; j < black_count; j++)
    {

        printf("%c\t", captured_pieces[2][j]);
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
