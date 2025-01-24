#include <stdbool.h>
#ifndef BOARD_H
#define BOARD_H


typedef struct field_t{
    int row; //Wiersz do którego nalezy pole
    int col; //Kolumna do ktorej nalezy pole
    bool isMine; //Czy pole jest miną
    bool isFlagged; //Czy pole jest oflagowane
    bool isRevealed; //Czy pole jest odkryte

}field_t;

typedef struct board_t {
    field_t **board; //Tablica 2d przechowująca pola
    int width; //Szerokość planszy
    int height; //Wysokość planszy
    int numOfMines; //Obecna liczba min na planszy
    bool areMinesGenerated; //Czy miny zostały już wygenerowane
    int score; //Wynik gracza
}board_t;


//Doostępne trudności gry
typedef enum {
    EASY,
    MEDIUM,
    HARD,
    CUSTOM //Można ustawić własny rozmiar planszy i wybrać liczbe min
} difficulty_t;

//Fnkcje planszy

board_t* init_board(difficulty_t difficulty); // inicjalizuje planszę
void display_board(board_t* board); // wyświetla planszę
void place_mines(board_t *board, int firstRow, int firstCol); // umieszcza miny na planszy
void free_board(board_t* board); // zwalnia pamięć planszy
void reveal_all_mines(board_t* board); // odsłania wszystkie miny



#endif