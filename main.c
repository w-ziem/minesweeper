#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "engine.h"
#include "game.h"
#include "score.h"

int main(int argc, char *argv[]){
    srand(time(NULL)); // Seed random number generator
    //Ustawia wybraną trudność
    char playerName[20];
    get_player_name(playerName);
    difficulty_t chosenDifficulty = get_difficulty_from_user();
    //Inicjalizuje plansze i dobiera jej wielkość
    board_t* board = init_board(chosenDifficulty);
    //Wyswietla poczatkowy stan planszy
    display_board(board);

    while(true){
        calculate_score(chosenDifficulty, board);
        get_move(board);
        clear_screen();
        display_board(board);
        int game_status = check_game_finished(board);
        // printf("Game status: %d\n", game_status);
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