#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "engine.h"
#include "game.h"
#include "score.h"
#include "readingFromFile.h"

// Funkcja główna programu
int main(int argc, char** argv) {
    srand(time(NULL));  // Inicjalizacja generatora liczb losowych

    char playerName[20]; // Tablica na nazwę gracza

    if (argc > 1) {  
        // Jeśli podano argument z plikiem wejściowym, wczytaj grę z pliku
        board_t* board;  // Wskaźnik na strukturę planszy
        read_game_from_file(argv[1], &board, playerName); // Wczytanie gry z pliku
    } else {
        // Jeśli nie podano pliku, rozpocznij nową grę
        get_player_name(playerName);  // Pobranie nazwy gracza

        // Pobranie wybranego poziomu trudności od użytkownika
        difficulty_t chosenDifficulty = get_difficulty_from_user();

        // Inicjalizacja planszy na podstawie wybranego poziomu trudności
        board_t* board = init_board(chosenDifficulty);

        clear_screen(); // Wyczyszczenie ekranu konsoli
        display_board(board); // Wyświetlenie początkowego stanu planszy

        // Główna pętla gry
        int game_status = CONTINUE; // Status gry (kontynuacja)

        while (game_status == CONTINUE) {
            // Obliczanie i wyświetlanie wyniku gracza
            calculate_score(chosenDifficulty, board);
            // Obsługa ruchu gracza
            handle_move(board);
            // Czyszczenie ekranu i aktualizacja planszy
            clear_screen();
            display_board(board);
            // Sprawdzanie, czy gra się zakończyła
            game_status = check_game_finished(board);
        }

        // Odkrycie wszystkich min po zakończeniu gry
        reveal_all_mines(board);
        clear_screen();
        display_board(board);

        // Zakończenie gry, wyświetlenie wyniku oraz zwalnianie zaalokowanej dla sturktur pamięci
        end_game(board, game_status, playerName, chosenDifficulty);
    }

    return EXIT_SUCCESS; // Program zakończył się pomyślnie
}

