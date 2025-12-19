#ifndef TYPES_H
#define TYPES_H

// Define LastMove structure
typedef struct
{
    int from_row;
    int from_col;
    int to_row;
    int to_col;
    char piece_moved;
} LastMove;

// Define gameState structure
typedef struct
{
    int white_king_moved;
    int black_king_moved;
    char board[8][8];
    int is_white_turn;
    int white_rook_a_moved;
    int black_rook_a_moved;
    int black_rook_h_moved;
    int white_rook_h_moved;
    LastMove *last_move;
} gameState;

#endif