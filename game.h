
#ifndef GAME_H
#define GAME_H

typedef struct field_t{
    int row;
    int col;
    bool isMine;
    bool isFlagged;
    bool isRevealed;

}field_t;

typedef struct board_t {
    field_t **board; //Tablica 2d przechowująca pola
    int width; //Szerokość planszy
    int height; //Wysokość planszy
    int numOfMines; //Obecna liczba min na planszy
    bool areMinesGenerated; //Czy miny zostały już wygenerowane
    int score; //Wynik gracza
}board_t;

typedef enum {
    EASY,
    MEDIUM,
    HARD,
    CUSTOM
} difficulty_t;

difficulty_t get_difficulty_from_user();
board_t* init_board(difficulty_t difficulty);
void display_board(board_t* board, difficulty_t difficulty);
void place_mines(board_t *board, int firstRow, int firstCol);
void free_board(board_t* board);
void clear_screen();
int calculate_revealed_fields(board_t* board, int ROWS, int COLS);
void calculate_score(difficulty_t difficulty, board_t* board);
#endif