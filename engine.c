#include "engine.h"
#include "score.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

void place_flag(board_t* board, int row, int col){
    board->board[row][col].isFlagged = !board->board[row][col].isFlagged;
}


void reveal_squares(board_t* board, int row, int col){
    // Sprawdź, czy pole jest w granicach planszy i czy nie jest już odkryte
    if (!is_valid_move(board, row, col) || board->board[row][col].isRevealed) {
        return;
    }

    // Odkryj bieżące poles
    board->board[row][col].isRevealed = true;

    // Jeśli bieżące pole ma sąsiadujące miny, zakończ
    if (get_number_of_adjacent_mines(row, col, board) >  0) {
        return;
    } 

    //jeżeli obecn pole nie sąsiaduje z minami to rekurencyjnie odkrywanie są sąsiedzi
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if ((i != 0 || j != 0) && is_valid_move(board, row+i, row+j)) { // Pomijamy bieżące pole
                reveal_squares(board, row + i, col + j); // ruchy góra dół zapewnia i, ruchy lewo prawo zapewnia j
            }
            }
    }

    
}



void handle_move(board_t* board) {
    int row;
    int col;
    char move; //f - flag r - reveal
    printf("Wprowadź ruch (akcja wiersz kolumna): \n");
    //pobiera ruch gracza
    scanf(" %c %d %d", &move, &row, &col);

    //debug
    printf("Wprowadzono ruch: row: %d col: %d \n", row, col);
    printf("Przeczytane wymiary planszy %d %d \n", board->height, board->width);
    //koniec debug

    //sprawdzanie poprawności wprowadzonego ruchu (czy jest w planszy)
    if(!is_valid_move(board, row, col)){
        printf("(!) Niedozwolony ruch. Spróbuj ponownie. \n");
        handle_move(board);
    } else if (board->board[row][col].isRevealed == true || board->board[row][col].isFlagged == true){
        printf("To pole jest już odkryte. Odkryj pole zakryte lub oflagowane.\n");
        handle_move(board);
    }else if(move == 'f'){ 
        place_flag(board, row, col); 
    } else if(move == 'r'){
        if(board->areMinesGenerated == true){
            reveal_squares(board, row, col);
        } 
        //jeżeli miny nie są wygenerowane, to przed odkryciem pól, ustawiane są miny, omijając pierwsze pole
        else{
            place_mines(board, row, col);
            reveal_squares(board, row, col);
        }
    } 

    //błędnie wprowadzony ruch
    else { //
        printf("(!) Niedozwolony ruch. Użyj f- flaga, lub r - odsłoń \n");
        handle_move(board);
    }
}

int get_number_of_adjacent_mines(int row, int col, board_t* board) {
    int count = 0;
    // Pętla przechodząca po 8 sąsiadach wokół danego pola
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = row + i;
            int newCol = col + j;

            // obecna komórka jest pomijana (row, col)
            if (i == 0 && j == 0) {
                continue;
            }

            // Sprawdzanie czy komórka (sąsiad) jest w granicach
            if (newRow >= 0 && newRow < board->height && newCol >= 0 && newCol < board->width) {
                // Sprawdzanie czy jest miną
                if (board->board[newRow][newCol].isMine) {
                    count++;
                }
            }
        }
    }
    return count;
}


bool is_valid_move(board_t* board, int moveRow, int moveCol){
    if(moveRow >= 0 && moveRow < board->height && moveCol >= 0 && moveCol < board->width){
        return true;
    } else {
        return false;
    }
}



int check_game_finished(board_t* board){
    int usedFields = 0;
    for(int i = 0; i < board->height; i++){
        for(int j = 0; j < board->width; j++){
            if(board->board[i][j].isMine && board->board[i][j].isRevealed){
                return LOSS;
            } else if(board->board[i][j].isRevealed || board->board[i][j].isFlagged){
                usedFields++;
            }
        }
    }
    //jeżeli liczba pól odkrytych i oznaczonych flagą jest równa liczbie pól na planszy
    if(usedFields == (board->width * board->height)){ 
        return WIN;
    } else {
        return CONTINUE;
    }
}


void end_game(board_t* board, int result, char* playerName, difficulty_t difficulty){
    if(result == LOSS){
        printf("Przegrałeś! \n");
        switch (difficulty){
            case EASY:
                board->score= -50;
                break;
            case MEDIUM:
                board->score= -30;
                break;
            case HARD:
                board->score= -10;
                break;
            default:
                fprintf(stderr, "(!) Wynik niezapisany. \n");
                board->score=0;
                return;
        }
    } else if(result == WIN){
        printf("Wygrałeś! \n");
    }
    save_score(playerName, board->score);
    print_top_scores();
    //Zwalnianie pamięci planszy
    free_board(board);

}

