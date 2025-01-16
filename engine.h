//zadaniami silnika gry są pobieranie ruchu, wykonywanie go (odsłanianie pola, ustawianie flag, sprawdzanie wygranej i przegranej)

#ifndef ENGINE_H
#define ENGINE_H
#include <stdbool.h>
#include "game.h"

#define LOSS 0
#define WIN 1
#define CONTINUE 2


int get_move(board_t* board); // pobiera ruch gracza i zwraca wartość na danym polu
int get_number_of_adjacent_mines(int row, int col, board_t* board, int ROWS, int COLS); // zwraca liczbę min wokół danego pola
bool is_valid_move(board_t* board, int moveRow, int moveCol, int ROWS, int COLS); // sprawdza czy ruch jest poprawny
int check_game_finished(board_t* board); // sprawdza czy wszystkie pola bez min zostały odkryte lub oflagowane
void end_game(board_t* board, int result, char* playerName, difficulty_t difficulty); // kończy grę i wyświetla wynik
void place_flag(board_t* board, int row, int col); // ustawia flagę na danym polu
int reveal_square(board_t* board, int row, int col); // odsłania pole
void reveal_all_mines(board_t* board); // odsłania wszystkie miny


#endif // GAME_H