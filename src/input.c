#include "../include/input.h"
#include <stdio.h>
#include <ctype.h>
// checking character index validation
int valid_col(char *c)
{
    return (((*c >= 'A') && (*c <= 'H')) || ((*c >= 'a') && (*c <= 'h')));
}

// checking row number index validation
int valid_row(char *n)
{
    return ((*n >= '1') && (*n <= '8'));
}

// scanning inputs and printing Errors
void input_validation(char *from_col_char, char *to_col_char, char *from_row_char, char *to_row_char)
{

    int Error_flag = 1;
    while (Error_flag)
    {
        char c[4]; // from_char, from_row, to_char, to_row

        for (int i = 0; i < 4; i++)
        {
            scanf("%c", &c[i]);
            if (c[i] == ' ')
            {
                i--;
            }
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
            printf("Error Please try again !\n");
        }
    }
}

// convert from (A to H)index to(0 to 7)index
void convert_col_index(char *from_col_char, char *to_col_char, int *from_col, int *to_col)
{
    *from_col_char = toupper(*from_col_char);
    *to_col_char = toupper(*to_col_char);
    *from_col = *from_col_char - 'A';
    *to_col = *to_col_char - 'A';
}

// convert from(1 to 8)index to (0 to 7)index
void convert_row_index(char *from_row_char, char *to_row_char, int *from_row, int *to_row)
{
    *from_row = *from_row_char - '1';
    *to_row = *to_row_char - '1';
}