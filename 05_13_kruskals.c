#include <stdio.h>
#include <stdlib.h>

#define V 100   // Maximum vertices
#define E 1000  // Maximum edges

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent, rank;
};

// Find set of an element i (with path compression)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union of two sets (by rank)
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare function for qsort
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Kruskal’s MST Algorithm
void KruskalMST(struct Edge edges[], int V, int E) {
    struct Edge result[V]; // Store MST edges
    int e = 0; // Index for result[]
    int i = 0; // Index for sorted edges

    // Step 1: Sort edges by weight
    qsort(edges, E, sizeof(edges[0]), compareEdges);

    // Allocate memory for subsets
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Step 2: Pick smallest edges and check for cycles
    while (e < V - 1 && i < E) {
        struct Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) { // No cycle
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print result
    printf("Edges in Minimum Spanning Tree:\n");
    int totalWeight = 0;
    for (i = 0; i < e; i++) {
        printf("%d -- %d \t%d\n", result[i].src, result[i].dest, result[i].weight);
        totalWeight += result[i].weight;
    }
    printf("Total weight of MST: %d\n", totalWeight);
}

int main() {
    int Vn, En;
    printf("Enter number of vertices: ");
    scanf("%d", &Vn);
    printf("Enter number of edges: ");
    scanf("%d", &En);

    struct Edge edges[E];

    printf("Enter each edge (src dest weight):\n");
    for (int i = 0; i < En; i++) {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    KruskalMST(edges, Vn, En);

    return 0;
}
