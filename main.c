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

    //Powtawrza dopóki gra trwa
    int game_status = CONTINUE;
    while(game_status == CONTINUE){
        //Wyświetla wynik
        calculate_score(chosenDifficulty, board);
        //Obsługuje ruch
        get_move(board);
        //Usuwa poprzednie wyświetlenie planszy
        clear_screen();
        //Wyświetla odświeżoną plansze
        display_board(board);
        //Zmienna sprawdzająca czy gra nadal trwa
        game_status = check_game_finished(board);
    }
    //jeżeli wyjdzie z pętli to status gry wykazuuje, że gra się zakończyła

    //wszystkie miny zostają odkryte
    reveal_all_mines(board);
    //Usuwa poprzednie wyświetlenie planszy i wyświetla plansze z odkrytymi minami
    clear_screen();
    display_board(board);
    //Kończy grę i wyświetla wynik
    end_game(board, game_status, playerName, chosenDifficulty);

    //Zwalnianie pamięci planszy
    free_board(board);

    return EXIT_SUCCESS;
}