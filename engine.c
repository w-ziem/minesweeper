#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define LOSS 0
#define WIN 1
#define CONTINUE 2

void place_flag(board_t* board, int row, int col){
    board->board[row][col].isFlagged = !board->board[row][col].isFlagged;
}
int reveal_square(board_t* board, int row, int col){
    if (board->board[row][col].isRevealed==false){
        board->board[row][col].isRevealed=true;
    }else {
        printf("To pole jest już odkryte. Odkryj pole zakryte lub oflagowane.\n");
    }
}

void reveal_all_mines(board_t* board){
    for (int i=0; i<board->width; i++){
        for (int j=0; j<board->height; j++){
            if (board->board[i][j].isMine){
                board->board[i][j].isRevealed=true;
            }
        }
    }
}


int get_move(board_t* board) {
    int row, col;
    char move; //f - flag r - reveal
    printf("Wprowadź ruch (akcja wiersz kolumna): \n");
    //pobiera ruch gracza
    scanf("%c %d %d", &move, &row, &col);
    //sprawdzanie poprawności wprowadzonego ruchu (czy jest w planszy)
    if(!is_valid_move(board, row, col, board->height, board->width)){
        printf("(!) Niedozwolony ruch. Spróbuj ponownie. \n");
        get_move(board);
    } else if(move == 'f'){ 
        place_flag(board, row, col); 
    } else if(move == 'r'){
        reveal_square(board, row, col);
    } 
    //błędnie wprowadzony ruch
    else { //
        printf("(!) Niedozwolony ruch. Użyj f- flaga, lub r - odsłoń \n");
        get_move(board);
    }
    //Wygenerowanie min jeśli już nie są wygenerowane
    if (!board->areMinesGenerated) {
        place_mines(board, row, col);
        printf("Wygenerowano miny! \n");
    }
}

int get_number_of_adjacent_mines(int row, int col, board_t* board, int ROWS, int COLS) {
    int count = 0;
    // Loop through the 8 neighboring cells
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = row + i;
            int newCol = col + j;

            // Skip the current cell (row, col)
            if (i == 0 && j == 0) {
                continue;
            }

            // Check if the neighboring cell is within bounds
            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
                // Check if the neighboring cell is a mine
                if (board->board[newRow][newCol].isMine) {
                    count++;
                }
            }
        }
    }
    return count;
}

bool is_valid_move(board_t* board, int moveRow, int moveCol, int ROWS, int COLS){
    if(moveRow >= 0 && moveRow <= ROWS && moveCol >= 0 && moveCol <= COLS){
        return true;
    } else {
        return false;
    }
}

int check_game_finished(board_t* board, int ROWS, int COLS){
    int usedFields = 0;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            if(board->board[i][j].isMine && board->board[i][j].isRevealed){
                return LOSS;
            } else if(board->board[i][j].isRevealed || board->board[i][j].isFlagged){
                usedFields++;
            }
        }
    }
    if(usedFields == (ROWS * COLS)-board->numOfMines){ //jeżeli liczba pól odkrytych i oznaczonych flagą jest równa liczbie pól na planszy - liczbie min
        return WIN;
    } else {
        return CONTINUE;
    }
}


void end_game(int result){
    if(result == LOSS){
        printf("Przegrałeś! \n");
        //TODOOOO
    } else if(result == WIN){
        printf("Wygrałeś! \n");
        //TODOOOO
    }
}