#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "engine.h"
#include "game.h"
#include "score.h"

int main(int argc, char *argv[]){
    //Ustawienia generatora losowego
    srand(time(NULL)); 
    //Ustawienie maksymalnej wielkości nicku gracza
    char playerName[20];
    //Wczytuje nick wybrany przez gracza
    get_player_name(playerName);
    //Wczytuje trudność wybraną przez użytkownika
    difficulty_t chosenDifficulty = get_difficulty_from_user();
    //Inicjalizuje plansze i dobiera jej wielkość
    board_t* board = init_board(chosenDifficulty);
    //Wyswietla poczatkowy stan planszy
    display_board(board);

    //Powtawrza w nieskończoność
    while(true){
        //Wyświetla wynik
        calculate_score(chosenDifficulty, board);
        //Obsługuje ruch
        get_move(board);
        //Usuwa poprzednie wyświetlenie planszy
        clear_screen();
        //Wyświetla odświeżoną plansze
        display_board(board);
        //Zmienna sprawdzająca czy gra nadal trwa
        int game_status = check_game_finished(board);
        if (game_status != CONTINUE) {
            reveal_all_mines(board);
            clear_screen();
            display_board(board);
            end_game(board, game_status, playerName, chosenDifficulty);
            print_top_scores();
            break;
        }
    }
    

    //Zwalnianie pamięci planszy
    free_board(board);

    return EXIT_SUCCESS;
}