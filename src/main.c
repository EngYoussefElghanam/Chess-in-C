#include <stdio.h>
#include "board.h"
#include "display.h"
#include "input.h"
#include "moves.h"
#include "game.h"
#include "file_io.h"
#include "history.h"

/*
 * MAIN FILE
 *
 * RESPONSIBLE FOR: Main game loop, coordinating all modules
 *
 * TASKS:
 * - Create the main game loop
 * - Display welcome message
 * - Ask for move from current player
 * - Call input parser
 * - Call move validator
 * - If valid, make the move
 * - Check for check/checkmate/stalemate
 * - Switch turns
 * - Handle special commands (save, load, undo, redo, quit)
 *
 * GAME LOOP STRUCTURE:
 * 1. Display board
 * 2. Display whose turn
 * 3. Get input from player
 * 4. Check if it's a command (save/load/undo/redo/quit)
 * 5. If it's a move, validate it
 * 6. If valid, make the move and update history
 * 7. Check for check/checkmate/stalemate
 * 8. Switch turns
 * 9. Repeat
 */

int main()
{
    // Variables needed
    char board[8][8];
    char white_captured[16];
    char black_captured[16];
    int white_captured_count = 0;
    int black_captured_count = 0;
    int is_white_turn = 1; // 1 = white's turn, 0 = black's turn
    int game_over = 0;

    // Initialize
    initialize_board(board);
    clear_history();

    printf("Welcome to Chess!\n");
    printf("Commands: Enter move (e.g., E2E4), 'save', 'load', 'undo', 'redo', 'quit'\n\n");

    // Main game loop
    while (!game_over)
    {
        // TODO: Implement game loop
        // 1. Display game state
        // 2. Get input
        // 3. Process input
        // 4. Check game end conditions
        // 5. Switch turns

        // Temporary - just display board once and exit
        display_game(board, white_captured, white_captured_count,
                     black_captured, black_captured_count, is_white_turn);
        break;
    }

    printf("Thanks for playing!\n");
    return 0;
}