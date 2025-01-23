#ifndef READINGFROMFILE_H
#define READINGFROMFILE_H

#include "game.h"

int read_game_from_file(const char* filename, board_t** board, char* player_name);//Czyta i obsługuje dane z pliku
difficulty_t get_difficulty_from_file(FILE* file); //Czyta trudność z pliku
void handle_move_from_file(board_t* board, char action, int row, int col); //Obsługuje ruchy w pliku

#endif