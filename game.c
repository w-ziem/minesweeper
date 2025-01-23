#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "game.h"
#include "engine.h"
#include "board.h"


difficulty_t get_difficulty_from_user() {
    char input[10];
    
    difficulty_t difficulty;

    printf("Wybierz trudność (easy, medium, hard, custom): ");
    fgets(input, sizeof(input), stdin); // Wczytujemy dane od użytkownika
    input[strcspn(input, "\n")] = 0; // Usuwamy znak nowej linii na końcu

    if (strcmp(input, "easy") == 0) {
        difficulty = EASY;
    } else if (strcmp(input, "medium") == 0) {
        difficulty = MEDIUM;
    } else if (strcmp(input, "hard") == 0) {
        difficulty = HARD;
    } else if (strcmp(input, "custom") == 0) {
        difficulty = CUSTOM;
        
    } else {
        printf("Nieprawidłowa trudność! Domyślnie ustawiono medium.\n");
        difficulty = MEDIUM;
    }

    return difficulty;
}


void get_player_name(char* playerName){
    printf("Podaj nazwę gracza (maksymalnie 20 znaków): ");
    fgets(playerName, 20, stdin); //wczytuje nazwę gracza
    playerName[strcspn(playerName, "\n")] = 0; //usuwa znak nowej linii na końcu
}


int calculate_revealed_fields(board_t* board, int ROWS, int COLS) {
    int revealedCount = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board->board[i][j].isRevealed) {
                revealedCount++;
            }
        }
    }

    return revealedCount;
}


void clear_screen() {
    system("clear");
}


