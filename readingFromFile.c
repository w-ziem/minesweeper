#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "engine.h"

// Funkcja inicjalizuje planszę na podstawie pliku i wybranego poziomu trudności
board_t* init_board_from_file(difficulty_t difficulty, FILE* file) {
    int width, height, mines;
    board_t *board = malloc(sizeof(board_t));  // Alokujemy pamięć dla struktury board
    if (board == NULL) {
        // Obsługa błędu alokacji pamięci
        printf("Błąd alokacji pamięci.\n");
        exit(1);  // Zakończenie programu w przypadku braku pamięci
    }

    // Ustawienia parametrów planszy w zależności od poziomu trudności
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
            // Wczytaj wymiary i liczbę min dla niestandardowego poziomu trudności
            fscanf(file, "%d %d %d", &width, &height, &mines);
            board->width  = width;
            board->height = height;
            board->numOfMines = mines;
            break;
        default:
            // Domyślna konfiguracja planszy w przypadku nieznanego poziomu trudności
            board->width  = 16;
            board->height = 16;
            board->numOfMines = 10;
            break;
    }

    // Inicjalizacja dodatkowych pól planszy
    board->score = 0;
    board->areMinesGenerated = false;

    // Alokacja pamięci dla dwuwymiarowej tablicy reprezentującej pola planszy
    board->board = malloc(board->height * sizeof(field_t*));
    for (int i = 0; i < board->height; i++) {
        board->board[i] = malloc(board->width * sizeof(field_t));
    }

    // Ustawienia początkowe dla każdego pola na planszy
    for (int i = 0; i < board->height; i++) {
        for (int j = 0; j < board->width; j++) {
            board->board[i][j].row = i;
            board->board[i][j].col = j;
            board->board[i][j].isMine = false;
            board->board[i][j].isFlagged = false;
            board->board[i][j].isRevealed = false;
        }
    }

    return board; // Zwracamy wskaźnik na zainicjalizowaną planszę
}

// Funkcja obsługuje ruchy wczytane z pliku
void handle_move_from_file(board_t* board, char action, int row, int col) {
    // Sprawdzanie, czy ruch jest prawidłowy
    if (!is_valid_move(board, row, col)) {
        printf("(!) Niedozwolony ruch: %c %d %d\n", action, row, col);
        return;
    }

    // Sprawdzenie, czy pole jest już odkryte lub oflagowane
    if (board->board[row][col].isRevealed || board->board[row][col].isFlagged) {
        printf("Pole (%d, %d) jest już odkryte lub oflagowane.\n", row, col);
        return;
    }

    // Obsługa akcji flagowania pola
    if (action == 'f') {
        place_flag(board, row, col);
    }
    // Obsługa akcji odkrycia pola
    else if (action == 'r') {
        if (board->areMinesGenerated) {
            reveal_squares(board, row, col);
        } else {
            // Pierwszy ruch - generowanie min
            place_mines(board, row, col);
            reveal_squares(board, row, col);
        }
    }
}

// Funkcja wczytuje grę z pliku
int read_game_from_file(const char* filename, board_t* board, char* player_name) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Nie można otworzyć pliku");
        exit(EXIT_FAILURE); // Zakończenie programu w przypadku błędu otwarcia pliku
    }

    // Wczytanie nazwy gracza
    if (fgets(player_name, 100, file) == NULL) {
        printf("Błąd wczytywania nazwy gracza.\n");
        exit(EXIT_FAILURE);
    }

    // Wczytanie poziomu trudności
    char input[100];
    fgets(input, sizeof(input), file);
    input[strcspn(input, "\n")] = 0; // Usunięcie znaku nowej linii

    // Mapowanie poziomu trudności na odpowiednią wartość
    difficulty_t difficulty;
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

    // Inicjalizacja planszy na podstawie poziomu trudności i pliku
    board = init_board_from_file(difficulty, file);

    // Wczytywanie kolejnych ruchów
    char action;
    int row, col;
    while (fscanf(file, " %c %d %d", &action, &row, &col) == 3) {
        if (action == 'r' || action == 'f') {
            handle_move_from_file(board, action, row, col);
            display_board(board);
            calculate_score(difficulty, board);
            if (check_game_finished(board) != CONTINUE) {
                reveal_all_mines(board);
                clear_screen();
                display_board(board);
                end_game(board, check_game_finished(board), player_name, difficulty);
                free_board(board);
                return EXIT_SUCCESS;
            }
        } else {
            printf("Nieprawidłowa akcja: %c\n", action);
        }
    }

    fclose(file); // Zamknięcie pliku po zakończeniu odczytu

    return 0; //funkcja zakończona sukcesem
}
