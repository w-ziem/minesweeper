#include "board.h"
#ifndef GAME_H
#define GAME_H


difficulty_t get_difficulty_from_user(); //ustawia trudność gry (domyślnie na średnią)
void clear_screen(); // czyści ekran
int calculate_revealed_fields(board_t* board, int ROWS, int COLS); // zlicza odkryte pola
void calculate_score(difficulty_t difficulty, board_t* board); // oblicza wynik gracza
void get_player_name(char* playerName); // wczytuje nazwę gracza
#endif