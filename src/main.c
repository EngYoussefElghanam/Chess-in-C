#include <stdio.h>
#include "../include/board.h"
#include "../include/display.h"
#include "../include/input.h"
#include "../include/moves.h"
#include "../include/game.h"
#include "../include/file_io.h"
#include "../include/history.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../include/types.h"

int main()
{
    char board[8][8];
    initialize_board(board);
    gameState Gs = {0};
    memcpy(Gs.board, board, sizeof(Gs.board));
    display_board(Gs.board);
    Gs.is_white_turn = 1;
    Gs.black_king_moved = 0;
    Gs.white_king_moved = 0;
    Gs.black_rook_a_moved = 0;
    Gs.black_rook_h_moved = 0;
    Gs.white_rook_h_moved = 0;
    Gs.white_rook_a_moved = 0;
    LastMove last_move = {-1, -1, -1, -1, '\0'};
    Gs.last_move = &last_move;
    Gs.position_count = 0;
    int undo_flag = 0;
    char *file = "^&@!~`'.txt";
    remove(file);

    char fromcol, fromrow, tocol, torow;
    char promoted_to = '\0';
    int from_row, to_row, from_col, to_col;
    char captured_pieces[2][16];

    // Initialize captured pieces arrays
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            captured_pieces[i][j] = '\0';
        }
    }

    int game_count = 0;
    int white_capture_count = 0;
    int black_capture_count = 0;

    // initial game state saving
    save_game_state(board, captured_pieces, &Gs.is_white_turn);

    int game_running = 1;

    while (game_running)
    {
        // Check for draw by insufficient material
        if (is_draw_by_insufficient_material(board))
        {
            printf("###################################\n");
            printf("#                                 #\n");
            printf("#   Draw by insufficient material #\n");
            printf("#             Draw🤝              #\n");
            printf("#                                 #\n");
            printf("###################################\n");
            break;
        }

        // Check for draw by repetition
        if (is_draw_by_repetition(&Gs))
        {
            printf("Draw by repetition is reached!\n");
            printf("Do you want to claim it? (y/n): ");
            char response;
            for (int i = 0; i < 1; i++)
            {
                scanf("%c", &response);
                if ((response == ' ') || (response == '\n') || (response == '\t'))
                {
                    i--;
                }
            }
            // Clear input buffer
            while (getchar() != '\n')
                ;

            if (response == 'y' || response == 'Y')
            {
                printf("###################################\n");
                printf("#                                 #\n");
                printf("#      Draw by repetition         #\n");
                printf("#             Draw🤝              #\n");
                printf("#                                 #\n");
                printf("###################################\n");
                break;
            }
            else
            {
                printf("Draw by repetition declined. Continue playing.\n");
            }
        }

        // Check for stalemate
        if (is_stalemate(Gs.board, Gs.is_white_turn))
        {
            printf("###################################\n");
            printf("#                                 #\n");
            printf("#           Stalemate⛓️            #\n");
            printf("#             Draw                #\n");
            printf("#                                 #\n");
            printf("###################################\n");
            break;
        }

        // Check for checkmate
        if (is_checkmate(Gs.board, Gs.is_white_turn))
        {
            printf("###################################\n");
            printf("#           Checkmate☠️            #\n");
            printf("#                                 #\n");
            Gs.is_white_turn ? printf("#            Black Won            #\n") : printf("#            White Won            #\n");
            printf("###################################\n");
            break;
        }

        // Check if king is in check
        if (is_king_in_check(Gs.board, Gs.is_white_turn))
        {
            printf("⚠️ ====Check====⚠️ \n");
        }

        printf("\n%s's turn. Enter your move (e.g., 'e2e4'), or command (DRAW/RESIGN): ",
               Gs.is_white_turn ? "White" : "Black");

        // Read input
        char c[4];
        for (int i = 0; i < 4; i++)
        {
            scanf("%c", &c[i]);
            if ((c[i] == ' ') || (c[i] == '\n') || (c[i] == '\t'))
            {
                i--;
            }
        }

        // Convert to uppercase for command checking
        for (int i = 0; i < 4; i++)
        {
            c[i] = toupper(c[i]);
        }

        // Clear input buffer
        while ((getchar()) != '\n')
            ;

        // Check for DRAW command
        if ((c[0] == 'D') && (c[1] == 'R') && (c[2] == 'A') && (c[3] == 'W'))
        {
            printf("%s offers a draw.\n", Gs.is_white_turn ? "White" : "Black");
            printf("%s, do you accept the draw? (y/n): ", Gs.is_white_turn ? "Black" : "White");

            char response;
            for (int i = 0; i < 1; i++)
            {
                scanf("%c", &response);
                if ((response == ' ') || (response == '\n') || (response == '\t'))
                {
                    i--;
                }
            }
            while (getchar() != '\n')
                ;

            if (response == 'y' || response == 'Y')
            {
                printf("###################################\n");
                printf("#                                 #\n");
                printf("#         Draw Accepted           #\n");
                printf("#             Draw🤝              #\n");
                printf("#                                 #\n");
                printf("###################################\n");
                break;
            }
            else
            {
                printf("Draw offer declined. Continue playing.\n");
                continue;
            }
        }

        // Check for RESIGN command
        if ((c[0] == 'R') && (c[1] == 'E') && (c[2] == 'S') && (c[3] == 'I'))
        {
            printf("###################################\n");
            printf("#            RESIGNED              #\n");
            printf("#                                 #\n");
            Gs.is_white_turn ? printf("#            Black Won            #\n") : printf("#            White Won            #\n");
            printf("###################################\n");
            break;
        }

        // Process as normal move
        fromcol = c[0];
        fromrow = c[1];
        tocol = c[2];
        torow = c[3];

        // Validate input format
        if (!valid_col(&fromcol) || !valid_col(&tocol) ||
            !valid_row(&fromrow) || !valid_row(&torow))
        {
            printf("ERROR!! Enter move (e.g E2E4) or command (DRAW/RESIGN/SAVE/LOAD/UNDO/REDO/QUIT):\n");
            continue;
        }

        convert_col_index(&fromcol, &tocol, &from_col, &to_col);
        convert_row_index(&fromrow, &torow, &from_row, &to_row);

        // Validate the move
        if (!is_valid_move(&Gs, from_row, from_col, to_row, to_col))
        {
            printf("❌ Illegal move! Try again.\n");
            continue;
        }

        // Check for pawn promotion
        promotion_input(board, &to_row, &from_row, &from_col, &promoted_to);

        // Handle pawn promotion
        if (will_promote(board, &to_row, &from_row, &from_col))
        {
            promote_pawn(board, torow, tocol, promoted_to);
        }

        // Store piece information before move
        char moving_piece = Gs.board[from_row][from_col];

        // Execute the move and get what was captured
        char captured_piece = execute_move(Gs.board, from_row, from_col, to_row, to_col);

        // Handle captured pieces

        if ((captured_piece == '-') || (captured_piece == '.'))
        {
            continue;
        }
        else
        {
            if (is_white_piece(captured_piece))
            {
                white_capture_count++;
                captured_pieces[1][white_capture_count] = captured_piece;
            }
            else
            {
                black_capture_count++;
                captured_pieces[2][black_capture_count] = captured_piece;
            }
        }

        undo_flag = 0; // after each move
        game_count++;  // after each move
        saving_correction(game_count);
        save_game_state(board, captured_pieces, &Gs.is_white_turn);
        printf("\033[2J\033[H"); // cleaning terminal before each display
        display_board(board);
        display_captured_pieces(captured_pieces, white_capture_count, black_capture_count);
        display_turn(Gs.is_white_turn);

        // Update castling rights based on piece movements
        if (tolower(moving_piece) == 'k')
        {
            if (Gs.is_white_turn)
                Gs.white_king_moved = 1;
            else
                Gs.black_king_moved = 1;
        }
        else if (tolower(moving_piece) == 'r')
        {
            if (Gs.is_white_turn)
            {
                if (from_col == 0 && from_row == 0)
                    Gs.white_rook_a_moved = 1;
                else if (from_col == 7 && from_row == 0)
                    Gs.white_rook_h_moved = 1;
            }
            else
            {
                if (from_col == 0 && from_row == 7)
                    Gs.black_rook_a_moved = 1;
                else if (from_col == 7 && from_row == 7)
                    Gs.black_rook_h_moved = 1;
            }
        }

        // Update last move information
        last_move.from_row = from_row;
        last_move.from_col = from_col;
        last_move.to_row = to_row;
        last_move.to_col = to_col;
        last_move.piece_moved = moving_piece;

        // Record position for draw detection
        record_position(&Gs);

        // Switch turns
        Gs.is_white_turn = !Gs.is_white_turn;
    }

    printf("\nGame Over! Thanks for playing.\n");
    return 0;
}

// where??!!
//  input_handling(char *from_col_char, char *to_col_char, char *from_row_char, char *to_row_char, char board[8][8], char captured_pieces[2][16], int *is_white_turn, int *is_black_turn, int *game_count, int *undo_flag, int *white_capture_count, int *black_capture_count)
// testing: is NULL in captured pieces works? for file load , redo ,undo