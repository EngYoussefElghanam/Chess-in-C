#ifndef FILE_IO_H
#define FILE_IO_H

/*
 * FILE I/O MODULE
 *
 * RESPONSIBLE FOR: Saving and loading games to/from files
 *
 * TASKS:
 * - Save current board state to a file
 * - Save captured pieces to file
 * - Save whose turn it is to file
 * - Load board state from a file
 * - Load captured pieces from file
 * - Load whose turn from file
 * - Handle file errors (file not found, etc.)
 *
 * NOTES:
 * - Use fopen, fprintf, fscanf, fclose
 * - Save files in the "saves/" folder
 * - File format is up to you - make it simple!
 * - Example: save each row of board on one line
 * - No need to save undo/redo history (project says so)
 */

// Save the current game to a file.
int save_game(char *file_name, char board[8][8], char captured_pieces[2][16], int *is_white_turn);

// load the current game to a file.
int load_game(char *file_name, char board[8][8], char captured_pieces[2][16], int *is_white_turn);
#endif