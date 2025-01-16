#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LOSS 0
#define WIN 1
#define CONTINUE 2

int get_move(board_t** board) {
    int row, col;
    char move; //f - flag r - reveal
    printf("Wprowadź ruch [akcja wiersz kolumna]: ");
    //pobiera ruch gracza
    scanf("%c %d %d", &move, &row, &col);
    //sprawdzanie poprawności wprowadzonego ruchu (czy jest w planszy)
    if(!is_valid_move(board, row, col)){
        printf("(!) Niedozwolony ruch. Spróbuj ponownie. \n");
        get_move();
    } else if(move == 'f'){ 
        place_flag(row, col); 
    } else if(move == 'r'){
        reveal_square(row, col);
    } 
    //błędnie wprowadzony ruch
    else { //
        printf("(!) Niedozwolony ruch. Użyj f- flaga, lub r - odsłoń \n");
        get_move();
    }
}

int get_number_of_adjacent_mines(int row, int col, board_t** board, int ROWS, int COLS){
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
                if (board[newRow][newCol].isMine) {
                    count++;
                }
            }
        }
    }
    return count;
}

bool is_valid_move(board_t** board, int moveRow, int moveCol, int ROWS, int COLS){
    if(moveRow >= 0 && moveRow < ROWS && moveCol >= 0 && moveCol < COLS){
        return true;
    } else {
        return false;
    }
}

int check_game_finished(board_t** board, int ROWS, int COLS){
    int usedFields = 0;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            if(board[i][j].isMine && board[i][j].isRevealed){
                return LOSS;
            } else if(board[i][j].isRevealed || board[i][j].isFlag){
                usedFields++;
            }
        }
    }
    if(usedFields == ROWS * COLS){ //jeżeli liczba pól odkrytych i oznaczonych flagą jest równa liczbie pól na planszy
        return WIN;
    } else {
        return CONTINUE;
    }
}


void end_game(int result){
    if(result == LOSS){
        printf("Przegrałeś! \n");
        ...
    } else if(result == WIN){
        printf("Wygrałeś! \n");
        ...
    }
}