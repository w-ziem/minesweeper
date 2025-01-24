#include "score.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void calculate_score(difficulty_t difficulty, board_t* board){
    int scoreMultiplier;
    int revealedFields=calculate_revealed_fields(board, board->height, board->width);
    //Ustawianie odpowiednich mnożników
    switch (difficulty)
    {
    case EASY:
        scoreMultiplier=1;
        break;
    case MEDIUM:
        scoreMultiplier=2;
        break;
    case HARD:
        scoreMultiplier=3;
        break;
    default:
        scoreMultiplier=2;
        break;
    }
    board->score=(revealedFields+1)*scoreMultiplier;
}


void save_score(char* playerName, int score){
    to_upper_case(playerName);
    FILE *file;
    char *filename = "scores.txt";
    // otwiera plik z wynikami
    file = fopen(filename, "r");
 
    // tworzy plik pomocniczy, gdzie będzie zapisywał wyniki
    char line[256];
    char tempFilename[] = "temp_scores.txt";
    FILE *tempFile = fopen(tempFilename, "w");
    if (tempFile == NULL) {
        fprintf(stderr, "(!) Nie udało się otworzyć pliku pomocniczego\n");
        fclose(file);
        return;
    }



    //przeszukuje plik z wynikami w celu znalezienia wyniku dla aktualnego gracza
    bool found = false;
    while (fgets(line, sizeof(line), file)) {
        char existingPlayer[256];
        int existingScore;
        sscanf(line, "%s %d", existingPlayer, &existingScore);
        //jeżeli wyniki znaleziony to nowy wynik jest sumowany z poprzednim i zapisywany w pliku pomocniczym
        if (strcmp(existingPlayer, playerName) == 0) {
            int newScore;
            newScore = existingScore + score;
            found = true;
            fprintf(tempFile, "%s %d\n", existingPlayer, newScore);
        } else{
            fprintf(tempFile, "%s %d\n", existingPlayer, existingScore);
        }
    }

    // jeżeli nie znaleziono wyniku dla gracza to zapisuje nowy wynik
    if (!found) {
        fprintf(tempFile, "%s %d\n", playerName, score);
    }

    fclose(file);
    fclose(tempFile);
    
    // usuwa stary plik z wynikami i zmienia nazwę pliku pomocniczego na nazwę pliku z wynikami
    remove(filename);
    rename(tempFilename, filename);
}



void to_upper_case(char* playerName){
    while (*playerName) {
        *playerName = toupper((unsigned char) *playerName);
        playerName++;
  }

}





void print_top_scores(void) {
    FILE *file;
    char *filename = "scores.txt";
    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "(!) Nie udało się otworzyć pliku %s\n", filename);
        return;
    }

    player_score_t scores[100]; // maksymalnie 100 wyników
    int count = 0;
    
    while (fscanf(file, "%s %d", scores[count].name, &scores[count].score) == 2) {
        count++;
    }
    fclose(file);
    // sortowanie wyników
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (scores[i].score < scores[j].score) {
                player_score_t temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }
    // wyświetlanie wyników
    printf("5 Najlepszych graczy:\n");
    for (int i = 0; i < count && i < 5; i++) {
        printf("%s %d\n", scores[i].name, scores[i].score);
    }
}