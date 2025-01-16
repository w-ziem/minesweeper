#ifndef SCORE_H
#define SCORE_H
#include "game.h"

typedef struct {
    char name[256];
    int score;
} player_score_t;

void calculate_score(difficulty_t difficulty, board_t* board); // Oblicza wynik gracza
void save_score(char* playerName, int score); // Zapisuje wynik gracza do pliku
void print_top_scores(void); // Wyświetla najlepsze 5 wyników
void to_upper_case(char* string); // Zamienia string na wielkie litery
#endif // SCORE_H