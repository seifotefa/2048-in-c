#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utility.h"

char getch_unix();

int main() {
    srand(time(NULL));
    initializeBoard();

    while (1) {
        printBoard();
        char ch = getch_unix();

        if (ch == 'q') {
            break;
        } else if (ch == 'a') {
            moveLeft();
        } else if (ch == 'd') {
            moveRight();
        } else if (ch == 'w') {
            moveUp();
        } else if (ch == 's') {
            moveDown();
        }

        if (isGameOver()) {
            printf("Game Over!\n");
            break;
        }
    }

    return 0;
}