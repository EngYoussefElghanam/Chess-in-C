#include "../include/game.h"
#include "../include/moves.h"
#include "../include/board.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
/* ================= POSITION HASHING ================= */

void create_position_hash(gameState *Gs, PositionHash *hash)
{
    // Flatten board into 64-byte array
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            hash->board_state[i * 8 + j] = Gs->board[i][j];
        }
    }

    // Encode castling rights (4 bits)
    hash->castling_rights =
        (!Gs->white_king_moved && !Gs->white_rook_h_moved ? 1 : 0) | // White kingside
        (!Gs->white_king_moved && !Gs->white_rook_a_moved ? 2 : 0) | // White queenside
        (!Gs->black_king_moved && !Gs->black_rook_h_moved ? 4 : 0) | // Black kingside
        (!Gs->black_king_moved && !Gs->black_rook_a_moved ? 8 : 0);  // Black queenside

    // Store en passant possibility
    hash->en_passant_col = -1;
    if (Gs->last_move != NULL && Gs->last_move->from_row != -1)
    {
        char piece = tolower(Gs->last_move->piece_moved);
        int from_row = Gs->last_move->from_row;
        int to_row = Gs->last_move->to_row;

        // Check if last move was a two-square pawn move
        if (piece == 'p' && abs(to_row - from_row) == 2)
        {
            hash->en_passant_col = Gs->last_move->to_col;
        }
    }

    hash->is_white_turn = Gs->is_white_turn;
}

/* ================= POSITION COMPARISON ================= */

int positions_equal(PositionHash *pos1, PositionHash *pos2)
{
    // Compare board state
    if (memcmp(pos1->board_state, pos2->board_state, 64) != 0)
        return 0;

    // Compare castling rights
    if (pos1->castling_rights != pos2->castling_rights)
        return 0;

    // Compare en passant possibility
    if (pos1->en_passant_col != pos2->en_passant_col)
        return 0;

    // Compare turn
    if (pos1->is_white_turn != pos2->is_white_turn)
        return 0;

    return 1;
}

/* ================= REPETITION DETECTION ================= */

int count_position_repetitions(gameState *Gs)
{
    PositionHash current;
    create_position_hash(Gs, &current);

    int count = 0;

    // Compare with all previous positions
    for (int i = 0; i < Gs->position_count; i++)
    {
        if (positions_equal(&current, &Gs->position_history[i]))
        {
            count++;
        }
    }

    return count;
}

int is_draw_by_repetition(gameState *Gs)
{
    // Threefold repetition: if current position occurred 2 times before,
    // this occurrence makes it the third time
    return (count_position_repetitions(Gs) > 2);
}

void record_position(gameState *Gs)
{
    if (Gs->position_count >= MAX_POSITION_HISTORY)
    {
        // Shift history if full
        for (int i = 0; i < MAX_POSITION_HISTORY - 1; i++)
        {
            Gs->position_history[i] = Gs->position_history[i + 1];
        }
        Gs->position_count = MAX_POSITION_HISTORY - 1;
    }

    create_position_hash(Gs, &Gs->position_history[Gs->position_count]);
    Gs->position_count++;
}

// Check for insufficient material draw
int is_draw_by_insufficient_material(char board[8][8])
{
    int white_knights = 0, white_bishops = 0;
    int black_knights = 0, black_bishops = 0;
    int white_pieces = 0, black_pieces = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char piece = board[i][j];
            if (is_square_empty(board, i, j))
                continue;

            char lower = tolower(piece);

            if (is_white_piece(piece))
            {
                white_pieces++;
                if (lower == 'n')
                    white_knights++;
                if (lower == 'b')
                    white_bishops++;
                // If any other piece exists (pawn, rook, queen), not insufficient
                if (lower == 'p' || lower == 'r' || lower == 'q')
                    return 0;
            }
            else
            {
                black_pieces++;
                if (lower == 'n')
                    black_knights++;
                if (lower == 'b')
                    black_bishops++;
                if (lower == 'p' || lower == 'r' || lower == 'q')
                    return 0;
            }
        }
    }

    // King vs King
    if (white_pieces == 1 && black_pieces == 1)
        return 1;

    // King + Knight vs King or King vs King + Knight
    if ((white_pieces == 2 && white_knights == 1 && black_pieces == 1) ||
        (black_pieces == 2 && black_knights == 1 && white_pieces == 1))
        return 1;

    // King + Bishop vs King or King vs King + Bishop
    if ((white_pieces == 2 && white_bishops == 1 && black_pieces == 1) ||
        (black_pieces == 2 && black_bishops == 1 && white_pieces == 1))
        return 1;

    return 0;
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

void promote_pawn(char board[8][8], int to_row, int to_col, int from_row, int from_col, char new_piece)
{

    char desired = tolower(new_piece);
    if (desired != 'q' && desired != 'r' &&
        desired != 'b' && desired != 'n')
    {
        printf("Cannot promote to that piece. Must be Q, R, B, or N.\n");
        return;
    }

    board[to_row][to_col] = (board[from_row][from_col] == 'p')
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
