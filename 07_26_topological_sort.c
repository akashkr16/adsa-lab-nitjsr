#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int n, graph[MAX][MAX], visited[MAX], stack[MAX], top = -1;

void topoDFS(int v) {
    visited[v] = 1;
    for (int i = 0; i < n; i++)
        if (graph[v][i] && !visited[i])
            topoDFS(i);
    stack[++top] = v;
}

void topologicalSort() {
    for (int i = 0; i < n; i++)
        if (!visited[i])
            topoDFS(i);

    printf("Topological Order: ");
    while (top >= 0)
        printf("%d ", stack[top--]);
    printf("\n");
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
    topologicalSort();
    return 0;
}
