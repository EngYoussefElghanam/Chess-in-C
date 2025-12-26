#ifndef TYPES_H
#define TYPES_H

#define MAX_POSITION_HISTORY 500 // Maximum positions to track

// Define LastMove structure
typedef struct
{
    int from_row;
    int from_col;
    int to_row;
    int to_col;
    char piece_moved;
} last_move;

// Define a position hash for tracking repetitions
typedef struct
{
    char board_state[64]; // Flattened board representation
    int castling_rights;  // Encoded castling availability
    int en_passant_col;   // -1 if no en passant, 0-7 for column
    int is_white_turn;
} position_hash;

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
    last_move *last_move;

    // For repetition detection
    position_hash position_history[MAX_POSITION_HISTORY];
    int position_count;
    int halfmove_clock; // For 50-move rule
} game_state;

#endif