#include "../include/game.h"
#include "../include/moves.h"
#include "../include/board.h"
#include <ctype.h>
#include <stdio.h>

void find_king(char board[8][8], int *king_row, int *king_col, int is_white_king)
{
    char piece;
    if (is_white_king)
    {
        piece = 'k';
    }
    else
    {
        piece = 'K';
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (is_square_empty(board, i, j))
            {
                continue;
            }
            if (get_piece_at(board, i, j) == piece)
            {
                *king_row = i;
                *king_col = j;
                return;
            }
        }
    }
}

int is_king_in_check(char board[8][8], int is_white_king)
{
    int king_row, king_col;
    LastMove dummy_move = {-1, -1, -1, -1, '\0'}; // this is dummy last move it is not possible but either way we don't care about last move now
    find_king(board, &king_row, &king_col, is_white_king);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char piece = get_piece_at(board, i, j);
            if (is_square_empty(board, i, j))
            {
                continue;
            }
            if (is_white_king && is_black_piece(piece))
            {
                if (is_valid_move(board, i, j, king_row, king_col, 0, &dummy_move))
                {
                    return 1;
                }
            }
            if (!is_white_king && is_white_piece(piece))
            {
                if (is_valid_move(board, i, j, king_row, king_col, 1, &dummy_move))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int can_promote(char board[8][8], int row, int col) // checking if pawn can promote
{
    char piece = board[row][col];
    if (piece == 'p' && row == 7)
    {
        return 1;
    }
    if (piece == 'P' && row == 0)
    {
        return 1;
    }
    return 0;
}

void promote_pawn(char board[8][8], int row, int col, char new_piece) // promoting pawn to the desired piece
{
    if (!can_promote(board, row, col))
    {
        printf("Not Eligible for promotion\n");
        return; // not eligible for promotion
    }
    char desired_piece = tolower(new_piece);
    if (desired_piece != 'r' && desired_piece != 'q' && desired_piece != 'b' && desired_piece != 'n')
    {
        printf("Cannot promote to that piece Must be Q, R, B, or N.\n");
        return;
    }
    char pawn = board[row][col];
    if (pawn == 'p')
    {
        board[row][col] = desired_piece;
    }
    if (pawn == 'P')
    {
        board[row][col] = toupper(desired_piece);
    }
}

// this is a helper function cause we will use it twice so write it once is better
int has_legal_moves(char board[8][8], int is_white_turn)
{
    LastMove dummy = {-1, -1, -1, -1, '\0'};
    // we will brute force it unfortunately
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (is_square_empty(board, i, j))
            {
                continue; // skip when squaree is empty
            }
            if ((is_white_turn && is_black_piece(board[i][j])) || (!is_white_turn && is_white_piece(board[i][j])))
            {
                continue; // skip if it is not our piece
            }
            // now we are sure it is our piece so let's check if there's any legal move
            char piece = board[i][j];
            for (int y = 0; y < 8; y++)
            {
                for (int h = 0; h < 8; h++)
                {
                    if ((h == j) && (y == i))
                    {
                        continue; // skip our position
                    }
                    // now check if it is legal to move
                    if (is_valid_move(board, i, j, y, h, is_white_turn, &dummy))
                    {
                        return 1; // if one legal move then we are fine it is not checkmate
                    }
                }
            }
        }
    }
    return 0;
}

int is_checkmate(char board[8][8], int is_white_king)
{
    return is_king_in_check(board, is_white_king) && !has_legal_moves(board, is_white_king);
}

int is_stalemate(char board[8][8], int is_white_turn)
{
    return !is_king_in_check(board, is_white_turn) && !has_legal_moves(board, is_white_turn);
}