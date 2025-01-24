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



board_t* init_board(difficulty_t difficulty){
    int width, height, mines;
    board_t *board = malloc(sizeof(board_t));  // Alokujemy pamięć dla struktury board
    if (board == NULL) {
        // Obsługa błędu alokacji pamięci
        printf("Błąd alokacji pamięci.\n");
        exit(1);  // Zakończenie programu
    }
         switch (difficulty) {
        case EASY:
            board->width = 9;
            board->height = 9;
            board->numOfMines = 10;
            break;
        case MEDIUM:
            board->width  = 16;
            board->height = 16;
            board->numOfMines = 40;
            break;
        case HARD:
            board->width  = 16;
            board->height = 30;
            board->numOfMines = 99;
            break;
        case CUSTOM:
            printf("Podano niestandardową trudność. Wynik nie będzie naliczny.\n");
            printf("Podaj niestandardowe wymiary planszy: (szerokość wysokość liczba_min)");
            scanf("%d %d %d", &width, &height, &mines);
            board->width  = width;
            board->height = height;
            board->numOfMines = mines;
            break;
        default:
            // Domyślna trudność jest ustawiana na średnią jeśli coś pójdzie nie tak
            board->width  = 16;
            board->height = 16;
            board->numOfMines = 10;
            break;
        
    }
    board->score = 0;
    board->areMinesGenerated = false;
    //Alokacja pamięci dla pól
    board->board = malloc(board->height * sizeof(field_t*));
    for (int i=0; i<board->height; i++){
        board->board[i] = malloc(board->width * sizeof(field_t));
    }

    // Inicjalizacja poszczególnych pól
    for (int i = 0; i < board->height; i++) {
        for (int j = 0; j < board->width; j++) {
            board->board[i][j].row = i;
            board->board[i][j].col = j;
            board->board[i][j].isMine = false;
            board->board[i][j].isFlagged = false;
            board->board[i][j].isRevealed = false;
        }
    }

    return board;

}

void place_mines(board_t *board, int firstRow, int firstCol) {
    int minesPlaced = 0;

    while (minesPlaced < board->numOfMines) {
        int randRow = rand() % board->height;
        int randCol = rand() % board->width;

        // Avoid placing a mine at the first move's position
        if (randRow == firstRow && randCol == firstCol) continue;

        // Avoid placing a mine on an already mined field
        if (board->board[randRow][randCol].isMine) continue;

        // Place the mine
        board->board[randRow][randCol].isMine = true;
        minesPlaced++;
    }
    board->areMinesGenerated = true;
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


