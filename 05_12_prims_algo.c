#include <stdio.h>
#include <limits.h>

#define V 100   // maximum number of vertices supported

// Find vertex with minimum key value not yet included in MST
int minKey(int key[], int mstSet[], int n) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < n; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Print the constructed MST
void printMST(int parent[], int graph[V][V], int n) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

// Prim’s algorithm
void primMST(int graph[V][V], int n) {
    int parent[V];  // Store constructed MST
    int key[V];     // Key values used to pick minimum weight edge
    int mstSet[V];  // Track included vertices

    // Initialize all keys as infinite
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Always include first vertex in MST
    key[0] = 0;
    parent[0] = -1; // First node is root of MST

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, n);
}

int main() {
    int n;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    int graph[V][V];
    printf("Enter adjacency matrix (0 if no edge):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("\nMinimum Spanning Tree using Prim’s Algorithm:\n");
    primMST(graph, n);

    return 0;
}
