
#ifndef GAME_H
#define GAME_H
#include <stdbool.h>

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

difficulty_t get_difficulty_from_user(); //ustawia trudność gry (domyślnie na średnią)
board_t* init_board(difficulty_t difficulty); // inicjalizuje planszę
void display_board(board_t* board); // wyświetla planszę
void place_mines(board_t *board, int firstRow, int firstCol); // umieszcza miny na planszy
void free_board(board_t* board); // zwalnia pamięć planszy
void clear_screen(); // czyści ekran
int calculate_revealed_fields(board_t* board, int ROWS, int COLS); // zlicza odkryte pola
void calculate_score(difficulty_t difficulty, board_t* board); // oblicza wynik gracza
void get_player_name(char* playerName); // wczytuje nazwę gracza
#endif