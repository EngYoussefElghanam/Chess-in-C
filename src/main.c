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
    memcpy((&Gs)->board, board, sizeof(Gs.board));
    display_board(Gs.board);
    (&Gs)->is_white_turn = 1;
    (&Gs)->black_king_moved = 0;
    (&Gs)->white_king_moved = 0;
    (&Gs)->black_rook_a_moved = 0;
    (&Gs)->black_rook_h_moved = 0;
    (&Gs)->white_rook_h_moved = 0;
    (&Gs)->white_rook_a_moved = 0;
    LastMove dummy = {-1, -1, -1, -1, '\0'};
    (&Gs)->last_move = &dummy;
    (&Gs)->position_count = 0;
    int undo_flag = 0;
    char *file = "^&@!~`'.txt";
    remove(file);
    int *is_white_turn = (&Gs)->is_white_turn;
    char fromcol, fromrow, tocol, torow;
    char promoted_to;
    int fromrow, torow, fromcol, tocol;
    char captured_pieces[2][16];
    int game_count = 0;
    save_game_state(board, captured_pieces, is_white_turn);
    int game_running = 1;
    while (game_running)
    {
        // checking king safety
        if (is_king_in_check(board, Gs.is_white_turn))
        {
            printf("⚠️====Check====⚠️\n");
        }
        if (is_checkmate(board, Gs.is_white_turn))
        {
            printf("###################################\n");
            printf("#           Checkmate☠️            #\n");
            printf("#                                 #\n");
            is_white_turn ? printf("#            Black Won            #\n") : printf("#            White Won            #\n");
            printf("###################################\n");
            break;
        }
        if (is_stalemate(board, Gs.is_white_turn))
        {
            printf("###################################\n");
            printf("#                                 #\n");
            printf("#           Stalemate⛓️            #\n");
            printf("#             Draw                #\n");
            printf("#                                 #\n");
            printf("###################################\n");
            break;
        }
        if (is_draw_by_repetition(&Gs))
        {
            printf("Draw by repetition is reached!\n");
            printf("Do you want to claim it? (y/n)");
            char response;
            for (int i = 0; i < 1; i++)
            {
                scanf("%c", &response);
                if ((response == ' ') || (response == '\n') || (response == '\t'))
                {
                    i--;
                }
            }
            if (strcmp(response, 'y') == 0)
            {
                printf("###################################\n");
                printf("#                                 #\n");
                printf("#           Draw by repetition    #\n");
                printf("#             Draw🤝              #\n");
                printf("#                                 #\n");
                printf("###################################\n");
                break;
            }
        }
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
        input_handling(&fromcol, &tocol, &fromrow, &torow, board, captured_pieces, is_white_turn, !is_white_turn, &game_count, &undo_flag);
        int from_row, to_row, from_col, to_col;
        convert_col_index(&fromcol, &tocol, &from_col, &to_col);
        convert_row_index(&fromrow, &torow, &from_row, &to_row);
        promotion_input(board, &to_row, &from_col, &promoted_to);
        // we need resign , draw !!
        return 0;
    }