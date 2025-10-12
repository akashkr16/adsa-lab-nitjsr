#include <stdio.h>
#define MAX 20

int board[MAX], n;

int isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return 0;
    }
    return 1;
}

void printBoard() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i] == j)
                printf(" Q ");
            else
                printf(" . ");
        }
        printf("\n");
    }
    printf("\n");
}

void solveNQueen(int row) {
    if (row == n) {
        printBoard();
        return;
    }
    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {
            board[row] = col;
            solveNQueen(row + 1);
        }
    }
}

int main() {
    printf("Enter number of queens: ");
    scanf("%d", &n);
    printf("All possible solutions:\n\n");
    solveNQueen(0);
    return 0;
}
