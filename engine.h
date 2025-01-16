//zadaniami silnika gry są pobieranie ruchu, wykonywanie go (odsłanianie pola, ustawianie flag, sprawdzanie wygranej i przegranej)

#ifndef GAME_H
#define GAME_H
#include <stdbool.h>


int get_move(void); // pobiera ruch gracza i zwraca wartość na danym polu
int get_number_of_adjacent_mines(int row, int col, board_t** board); // zwraca liczbę min wokół danego pola
int is_valid_move(int row, int col); // sprawdza czy ruch jest poprawny
bool check_game_finished(board_t** board); // sprawdza czy wszystkie pola bez min zostały odkryte lub oflagowane
void end_game(int result); // kończy grę i wyświetla wynik


#endif // GAME_H