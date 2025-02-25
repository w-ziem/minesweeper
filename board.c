#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "board.h"
#include "engine.h"


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
            printf("Podaj niestandardowe wymiary planszy: (szerokość wysokość liczba_min): ");
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
        board->score = 0;
    }

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


void display_board(board_t* board){
   // Wyświetl numerację kolumn
    printf("   "); // Odsunięcie dla numeracji wierszy
    for (int col = 0; col < board->width; col++) {
        printf("%2d ", col); // Dwucyfrowa numeracja kolumn
    }
    printf("\n");

    // Wyświetl poziomą linię oddzielającą nagłówki
    printf("   ");
    for (int col = 0; col < board->width; col++) {
        printf("---");
    }
    printf("\n");

    // Wyświetl planszę z numeracją wierszy
    for (int row = 0; row < board->height; row++) {
        printf("%2d|", row); // Numer wiersza z pionową linią
        for (int col = 0; col < board->width; col++) {
            if (board->board[row][col].isRevealed) {
                if (board->board[row][col].isMine) {
                    printf(" X "); // Pole z miną
                } else {
                    int adjucentMines=get_number_of_adjacent_mines(row,col,board);
                    printf(" %d ",adjucentMines); // Odsłonięte pole bez miny
                }
            } else if (board->board[row][col].isFlagged) {
                printf(" F "); // Pole z flagą
            } else {
                printf(" ■ "); // Zakryte pole
            }
        }
        printf("\n");
    }
    printf("Twój wynik to: %d\n",board->score);
}


void free_board(board_t* board) {
    //Zwalnianie pamięci dla każdego wiersza
    for (int i = 0; i < board->height; i++) {
        free(board->board[i]);
    }
    
    //Zwalnianie głównej tablicy 2d
    free(board->board);
    
    //Zwalnianie pamięci struktury board
    free(board);
}



void reveal_all_mines(board_t* board){
    for (int i = 0; i < board->height; i++){
        for (int j = 0; j < board->width; j++){
            if (board->board[i][j].isMine){
                board->board[i][j].isRevealed=true;
            }
        }
    }
}
