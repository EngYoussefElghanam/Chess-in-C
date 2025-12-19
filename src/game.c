#include "../include/game.h"
#include "../include/moves.h"
#include "../include/board.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* ================= KING FIND ================= */

int find_king(char board[8][8], int *king_row, int *king_col, int is_white_king)
{
    char piece = is_white_king ? 'k' : 'K';

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (!is_square_empty(board, i, j) &&
                get_piece_at(board, i, j) == piece)
            {
                *king_row = i;
                *king_col = j;
                return 1;
            }
        }
    }
    return 0; // king not found (invalid board)
}

/* ================= CHECK DETECTION ================= */

int is_king_in_check(char board[8][8], int is_white_king)
{
    int king_row, king_col;
    LastMove dummy_move = {-1, -1, -1, -1, '\0'};

    if (!find_king(board, &king_row, &king_col, is_white_king))
        return 0;

    gameState Gs = {0};
    memcpy(Gs.board, board, sizeof(Gs.board));
    Gs.is_white_turn = !is_white_king;
    Gs.last_move = &dummy_move;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (is_square_empty(board, i, j))
                continue;

            char piece = get_piece_at(board, i, j);

            if (is_white_king && !is_black_piece(piece))
                continue;
            if (!is_white_king && !is_white_piece(piece))
                continue;

            /* ---- Pawn attacks handled explicitly ---- */
            if (piece == 'p' || piece == 'P')
            {
                int dir = (piece == 'p') ? 1 : -1;
                if (i + dir == king_row &&
                    (j + 1 == king_col || j - 1 == king_col))
                    return 1;
                continue;
            }

            /* ---- Other pieces ---- */
            if (is_valid_move_no_check(&Gs, i, j, king_row, king_col))
                return 1;
        }
    }
    return 0;
}

/* ================= PROMOTION ================= */

int can_promote(char board[8][8], int row, int col)
{
    if (row < 0 || row > 7 || col < 0 || col > 7)
        return 0;

    char piece = board[row][col];
    return (piece == 'p' && row == 7) || (piece == 'P' && row == 0);
}

void promote_pawn(char board[8][8], int row, int col, char new_piece)
{
    if (!can_promote(board, row, col))
    {
        printf("Not Eligible for promotion\n");
        return;
    }

    char desired = tolower(new_piece);
    if (desired != 'q' && desired != 'r' &&
        desired != 'b' && desired != 'n')
    {
        printf("Cannot promote to that piece. Must be Q, R, B, or N.\n");
        return;
    }

    board[row][col] = (board[row][col] == 'p')
                          ? desired
                          : toupper(desired);
}

/* ================= LEGAL MOVE CHECK ================= */

int has_legal_moves(char board[8][8], int is_white_turn)
{
    LastMove dummy = {-1, -1, -1, -1, '\0'};
    gameState Gs = {0};

    memcpy(Gs.board, board, sizeof(Gs.board));
    Gs.is_white_turn = is_white_turn;
    Gs.last_move = &dummy;

    /* Disable castling in brute-force scan */
    Gs.white_king_moved = 1;
    Gs.black_king_moved = 1;
    Gs.white_rook_a_moved = 1;
    Gs.white_rook_h_moved = 1;
    Gs.black_rook_a_moved = 1;
    Gs.black_rook_h_moved = 1;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (is_square_empty(board, i, j))
                continue;

            if ((is_white_turn && is_black_piece(board[i][j])) ||
                (!is_white_turn && is_white_piece(board[i][j])))
                continue;

            for (int y = 0; y < 8; y++)
            {
                for (int h = 0; h < 8; h++)
                {
                    if (i == y && j == h)
                        continue;

                    if (is_valid_move(&Gs, i, j, y, h))
                        return 1;
                }
            }
        }
    }
    return 0;
}

/* ================= END STATES ================= */

int is_checkmate(char board[8][8], int is_white_king)
{
    return is_king_in_check(board, is_white_king) &&
           !has_legal_moves(board, is_white_king);
}

int is_stalemate(char board[8][8], int is_white_turn)
{
    return !is_king_in_check(board, is_white_turn) &&
           !has_legal_moves(board, is_white_turn);
}
