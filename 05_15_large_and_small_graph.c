#include <stdio.h>
#include <limits.h>

#define MAX 10

int graph[MAX][MAX], n;
int visited[MAX], path[MAX], pathIndex, smallest = INT_MAX, largest = 0;

void DFS(int start, int v, int depth) {
    visited[v] = 1;
    path[pathIndex++] = v;

    for (int i = 0; i < n; i++) {
        if (graph[v][i]) {
            if (!visited[i])
                DFS(start, i, depth + 1);
            else if (i == start && depth >= 2) {
                if (depth + 1 < smallest) smallest = depth + 1;
                if (depth + 1 > largest) largest = depth + 1;
            }
        }
    }
    visited[v] = 0;
    pathIndex--;
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) visited[j] = 0;
        pathIndex = 0;
        DFS(i, i, 0);
    }

    if (smallest == INT_MAX)
        printf("No cycle found.\n");
    else
        printf("Smallest cycle length: %d\nLargest cycle length: %d\n", smallest, largest);
    return 0;
}
