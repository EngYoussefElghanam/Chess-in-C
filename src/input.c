#include "../include/input.h"
#include <stdio.h>

// checking character index validation
int valid_char(char *c)
{
    return ((*c >= 65) && (*c <= 72));
}

// checking row number index validation
int valid_int(int *n)
{
    return ((*n >= 1) && (*n <= 8));
}

// scanning inputs and printing Errors
void input_validation(char *from_char, char *to_char, int *from_row, int *to_row)
{

    int Error_flag = 1;
    while (Error_flag)
    {
        scanf("%c%d%c%d", from_char, from_row, to_char, to_row);

        // cleaning buffer from extra length user input
        while ((getchar()) != '\n')
            ;

        // checking input validation
        if (valid_char(from_char) && valid_char(to_char) && valid_int(from_row) && valid_int(to_row))
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
void convert_col_index(char *from_char, char *to_char, int *from_col, int *to_col)
{
    *from_col = *from_char - 65;
    *to_col = *to_char - 65;
}

// convert from(1 to 8)index to (0 to 7)index
void convert_row_index(int *from_row, int *to_row)
{
    *from_row -= 1;
    *to_row -= 1;
}