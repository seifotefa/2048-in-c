#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h> // Include termios.h for terminal control
#include <unistd.h>  // Include unistd.h for STDIN_FILENO
#include <string.h> // For memcpy
#include "utility.h"

int board[BOARD_SIZE][BOARD_SIZE];

// Function to get a character from the keyboard without waiting for Enter
char getch_unix() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt); // Get the current terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply new settings
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old settings
    return ch;
}

void initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
    addRandomTile();
    addRandomTile();
}

void addRandomTile() {
    int emptyCells[BOARD_SIZE * BOARD_SIZE][2];
    int count = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                emptyCells[count][0] = i;
                emptyCells[count][1] = j;
                count++;
            }
        }
    }

    if (count > 0) {
        int index = rand() % count;
        int value = (rand() % 2 + 1) * 2;
        board[emptyCells[index][0]][emptyCells[index][1]] = value;
    }
}

// Add this function to check if a move changed the board
int boardChanged(int oldBoard[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (oldBoard[i][j] != board[i][j]) {
                return 1;
            }
        }
    }
    return 0;
}

void moveLeft() {
    int oldBoard[BOARD_SIZE][BOARD_SIZE];
    memcpy(oldBoard, board, sizeof(board));
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        // First, compact all non-zero numbers to the left
        int writePos = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != 0) {
                if (writePos != j) {
                    board[i][writePos] = board[i][j];
                    board[i][j] = 0;
                }
                writePos++;
            }
        }

        // Then merge adjacent equal numbers from left to right
        for (int j = 0; j < BOARD_SIZE - 1; j++) {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1]) {
                board[i][j] *= 2;
                board[i][j + 1] = 0;
            }
        }

        // Compact again after merging
        writePos = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != 0) {
                if (writePos != j) {
                    board[i][writePos] = board[i][j];
                    board[i][j] = 0;
                }
                writePos++;
            }
        }
    }

    if (boardChanged(oldBoard)) {
        addRandomTile();
    }
}

void moveRight() {
    int oldBoard[BOARD_SIZE][BOARD_SIZE];
    memcpy(oldBoard, board, sizeof(board));
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        // First, compact all non-zero numbers to the right
        int writePos = BOARD_SIZE - 1;
        for (int j = BOARD_SIZE - 1; j >= 0; j--) {
            if (board[i][j] != 0) {
                if (writePos != j) {
                    board[i][writePos] = board[i][j];
                    board[i][j] = 0;
                }
                writePos--;
            }
        }

        // Then merge adjacent equal numbers from right to left
        for (int j = BOARD_SIZE - 1; j > 0; j--) {
            if (board[i][j] != 0 && board[i][j] == board[i][j - 1]) {
                board[i][j] *= 2;
                board[i][j - 1] = 0;
            }
        }

        // Compact again after merging
        writePos = BOARD_SIZE - 1;
        for (int j = BOARD_SIZE - 1; j >= 0; j--) {
            if (board[i][j] != 0) {
                if (writePos != j) {
                    board[i][writePos] = board[i][j];
                    board[i][j] = 0;
                }
                writePos--;
            }
        }
    }

    if (boardChanged(oldBoard)) {
        addRandomTile();
    }
}

void moveUp() {
    int oldBoard[BOARD_SIZE][BOARD_SIZE];
    memcpy(oldBoard, board, sizeof(board));
    
    for (int j = 0; j < BOARD_SIZE; j++) {
        // First, compact all non-zero numbers upward
        int writePos = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i][j] != 0) {
                if (writePos != i) {
                    board[writePos][j] = board[i][j];
                    board[i][j] = 0;
                }
                writePos++;
            }
        }

        // Then merge adjacent equal numbers from top to bottom
        for (int i = 0; i < BOARD_SIZE - 1; i++) {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j]) {
                board[i][j] *= 2;
                board[i + 1][j] = 0;
            }
        }

        // Compact again after merging
        writePos = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i][j] != 0) {
                if (writePos != i) {
                    board[writePos][j] = board[i][j];
                    board[i][j] = 0;
                }
                writePos++;
            }
        }
    }

    if (boardChanged(oldBoard)) {
        addRandomTile();
    }
}

void moveDown() {
    int oldBoard[BOARD_SIZE][BOARD_SIZE];
    memcpy(oldBoard, board, sizeof(board));
    
    for (int j = 0; j < BOARD_SIZE; j++) {
        // First, compact all non-zero numbers downward
        int writePos = BOARD_SIZE - 1;
        for (int i = BOARD_SIZE - 1; i >= 0; i--) {
            if (board[i][j] != 0) {
                if (writePos != i) {
                    board[writePos][j] = board[i][j];
                    board[i][j] = 0;
                }
                writePos--;
            }
        }

        // Then merge adjacent equal numbers from bottom to top
        for (int i = BOARD_SIZE - 1; i > 0; i--) {
            if (board[i][j] != 0 && board[i][j] == board[i - 1][j]) {
                board[i][j] *= 2;
                board[i - 1][j] = 0;
            }
        }

        // Compact again after merging
        writePos = BOARD_SIZE - 1;
        for (int i = BOARD_SIZE - 1; i >= 0; i--) {
            if (board[i][j] != 0) {
                if (writePos != i) {
                    board[writePos][j] = board[i][j];
                    board[i][j] = 0;
                }
                writePos--;
            }
        }
    }

    if (boardChanged(oldBoard)) {
        addRandomTile();
    }
}

int isGameOver() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                return 0;
            }
            if (i < BOARD_SIZE - 1 && board[i][j] == board[i + 1][j]) {
                return 0;
            }
            if (j < BOARD_SIZE - 1 && board[i][j] == board[i][j + 1]) {
                return 0;
            }
        }
    }
    return 1;
}

void printBoard() {
    printf("\033[2J\033[H");  // Clear screen and move cursor to top
    printf("2048 Game\n");
    printf("Use WASD to move, Q to quit\n\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                printf(".    ");
            } else {
                printf("%-4d ", board[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}
    
