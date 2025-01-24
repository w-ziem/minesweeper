#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "board.h"
#include "engine.h"
#include "score.h"

// Simple test for place_flag
void test_place_flag() {
    board_t board;
    board.height = 5;
    board.width = 5;
    board.board = malloc(board.height * sizeof(field_t*));
    for (int i = 0; i < board.height; i++) {
        board.board[i] = malloc(board.width * sizeof(field_t));
    }

    // Initial state
    int row = 2, col = 2;
    board.board[row][col].isFlagged = false;
    place_flag(&board, row, col);
    assert(board.board[row][col].isFlagged == true);
    place_flag(&board, row, col);
    assert(board.board[row][col].isFlagged == false);

    printf("place_flag passed.\n");

    // Free memory
    for (int i = 0; i < board.height; i++) {
        free(board.board[i]);
    }
    free(board.board);
}

// Simple test for is_valid_move
void test_is_valid_move() {
    board_t board;
    board.height = 5;
    board.width = 5;
    board.board = malloc(board.height * sizeof(field_t*));
    for (int i = 0; i < board.height; i++) {
        board.board[i] = malloc(board.width * sizeof(field_t));
    }

    // Valid move (within bounds)
    assert(is_valid_move(&board, 2, 2) == true);
    // Invalid move (out of bounds)
    assert(is_valid_move(&board, 5, 5) == false);

    printf("is_valid_move passed.\n");

    // Free memory
    for (int i = 0; i < board.height; i++) {
        free(board.board[i]);
    }
    free(board.board);
}
void test_board_initialization() {
    // Test EASY difficulty
    printf("Testing EASY difficulty board initialization...\n");
    board_t* easy_board = init_board(EASY);
    display_board(easy_board);
    free_board(easy_board);
    printf("\nEASY initialization passed\n");

    // Test MEDIUM difficulty
    printf("\nTesting MEDIUM difficulty board initialization...\n");
    board_t* medium_board = init_board(MEDIUM);
    display_board(medium_board);
    free_board(medium_board);
    printf("\nMEDIUM initialization passed\n");

    // Test HARD difficulty
    printf("\nTesting HARD difficulty board initialization...\n");
    board_t* hard_board = init_board(HARD);
    display_board(hard_board);
    free_board(hard_board);
    printf("\nHARD initialization passed\n");

    // Test CUSTOM difficulty
    printf("\nTesting CUSTOM difficulty board initialization...\n");
    board_t* custom_board = init_board(CUSTOM);
    display_board(custom_board);
    free_board(custom_board);
    printf("\nCUSTOM initialization passed\n");
}

void test_mine_placement() {
    // Initialize a board with EASY difficulty
    printf("\nTesting mine placement on EASY board...\n");
    board_t* board = init_board(EASY);

    // Simulate first move at (0, 0)
    int firstRow = 0, firstCol = 0;
    place_mines(board, firstRow, firstCol);

    // Display the board after placing mines
    display_board(board);

    // Verify no mine at the first move position
    if (board->board[firstRow][firstCol].isMine) {
        printf("Test failed: Mine placed at first move position.\n");
    } else {
        printf("Test passed: No mine at first move position.\n");
    }

    // Reveal all mines and display the board
    printf("\nRevealing all mines...\n");
    reveal_all_mines(board);
    display_board(board);

    free_board(board);
}

// Main test runner
int main() {
    test_place_flag();
    test_is_valid_move();
    test_board_initialization();
    test_mine_placement();
    
    // You can add more tests for other functions here
    
    return 0;
}
