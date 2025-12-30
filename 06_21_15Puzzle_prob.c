#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4
#define INF 9999

int goal[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};

int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

struct Node {
    int mat[N][N];
    int x, y, cost, level;
    struct Node* parent;
};

int isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

int calculateCost(int mat[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (mat[i][j] && mat[i][j] != goal[i][j])
                count++;
    return count;
}

void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%2d ", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

void printPath(struct Node* root) {
    if (root == NULL) return;
    printPath(root->parent);
    printMatrix(root->mat);
}

struct Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, struct Node* parent) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            node->mat[i][j] = mat[i][j];

    int temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;

    node->cost = calculateCost(node->mat);
    node->level = level;
    node->parent = parent;
    node->x = newX;
    node->y = newY;
    return node;
}

void solve(int start[N][N], int x, int y) {
    struct Node* root = newNode(start, x, y, x, y, 0, NULL);
    root->cost = calculateCost(start);

    struct Node* pq[10000];
    int size = 0;
    pq[size++] = root;

    while (size > 0) {
        int minIndex = 0;
        for (int i = 1; i < size; i++)
            if (pq[i]->cost + pq[i]->level < pq[minIndex]->cost + pq[minIndex]->level)
                minIndex = i;

        struct Node* minNode = pq[minIndex];
        pq[minIndex] = pq[--size];

        if (minNode->cost == 0) {
            printf("Solution path:\n");
            printPath(minNode);
            printf("Total moves = %d\n", minNode->level);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = minNode->x + row[i];
            int newY = minNode->y + col[i];
            if (isSafe(newX, newY)) {
                pq[size++] = newNode(minNode->mat, minNode->x, minNode->y, newX, newY, minNode->level + 1, minNode);
            }
        }
    }
}

int main() {
    int start[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 12},
        {13, 14, 11, 15}
    };

    int x = 1, y = 2; // Blank tile position
    printf("Solving 15 Puzzle using Branch and Bound:\n\n");
    solve(start, x, y);
    return 0;
}
