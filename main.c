#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "engine.h"
#include "game.h"

int main(int argc, char *argv[]){
    srand(time(NULL)); // Seed random number generator
    //Ustawia wybraną trudność
    difficulty_t chosenDifficulty = get_difficulty_from_user();
    //Inicjalizuje plansze i dobiera jej wielkość
    board_t* board = init_board(chosenDifficulty);
    //Wyswietla poczatkowy stan planszy
    display_board(board, chosenDifficulty);

    while(true){
        calculate_score(chosenDifficulty, board);
        get_move(board);
        clear_screen();
        display_board(board, chosenDifficulty);
        int game_status = check_game_finished(board, board->height, board->width);
        printf("Game status: %d\n", game_status);
        if (game_status != 2) {
            reveal_all_mines(board);
            clear_screen();
            display_board(board, chosenDifficulty);
            end_game(game_status);
            break;
        }
    }
    

    //Zwalnianie pamięci planszy
    free_board(board);

    return 0;
}