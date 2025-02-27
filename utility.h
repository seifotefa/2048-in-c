#ifndef UTILITY_H
#define UTILITY_H

#define BOARD_SIZE 4

extern int board[BOARD_SIZE][BOARD_SIZE];

void initializeBoard();
void addRandomTile();
void moveLeft();
void moveRight();
void moveUp();
void moveDown();
int isGameOver();
void printBoard();
int boardChanged(int oldBoard[BOARD_SIZE][BOARD_SIZE]);

#endif