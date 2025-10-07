#include <stdio.h>

#define MAX 10
int graph[MAX][MAX], n;
int color[MAX], disc[MAX], fin[MAX], time = 0;

void DFSVisit(int u) {
    color[u] = 1;  // Gray
    disc[u] = ++time;
    for (int v = 0; v < n; v++) {
        if (graph[u][v]) {
            if (color[v] == 0) {
                printf("Tree Edge: %d -> %d\n", u, v);
                DFSVisit(v);
            } else if (color[v] == 1)
                printf("Back Edge: %d -> %d\n", u, v);
            else if (color[v] == 2) {
                if (disc[u] < disc[v])
                    printf("Forward Edge: %d -> %d\n", u, v);
                else
                    printf("Cross Edge: %d -> %d\n", u, v);
            }
        }
    }
    color[u] = 2;  // Black
    fin[u] = ++time;
}

void DFS() {
    for (int u = 0; u < n; u++)
        if (color[u] == 0)
            DFSVisit(u);
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    DFS();
    return 0;
}
