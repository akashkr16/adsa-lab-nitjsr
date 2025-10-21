#include <stdio.h>
#include <string.h>
#define MAX 100
int n, graph[MAX][MAX];
int timeD = 0;

int disc[MAX], low[MAX], parent[MAX];
int ap[MAX]; // articulation points

void DFS_AP_Bridge(int u) {
    int children = 0;
    disc[u] = low[u] = ++timeD;

    for (int v = 0; v < n; v++) {
        if (graph[u][v]) {
            if (disc[v] == -1) {
                children++;
                parent[v] = u;
                DFS_AP_Bridge(v);
                low[u] = (low[u] < low[v]) ? low[u] : low[v];

                if (parent[u] == -1 && children > 1)
                    ap[u] = 1;

                if (parent[u] != -1 && low[v] >= disc[u])
                    ap[u] = 1;

                if (low[v] > disc[u])
                    printf("Bridge: %d - %d\n", u, v);
            }
            else if (v != parent[u])
                if (low[u] > disc[v]) low[u] = disc[v];
        }
    }
}

void findAPsAndBridges() {
    memset(disc, -1, sizeof(disc));
    memset(low, -1, sizeof(low));
    memset(parent, -1, sizeof(parent));
    memset(ap, 0, sizeof(ap));

    for (int i = 0; i < n; i++)
        if (disc[i] == -1)
            DFS_AP_Bridge(i);

    printf("Articulation Points: ");
    for (int i = 0; i < n; i++)
        if (ap[i]) printf("%d ", i);
    printf("\n");
}

// --- Tarjan's Algorithm for SCC ---
int stack[MAX], top = -1, inStack[MAX];
void SCCUtil(int u) {
    static int time = 0;
    disc[u] = low[u] = ++time;
    stack[++top] = u;
    inStack[u] = 1;

    for (int v = 0; v < n; v++)
        if (graph[u][v]) {
            if (disc[v] == -1) {
                SCCUtil(v);
                if (low[u] > low[v]) low[u] = low[v];
            }
            else if (inStack[v] && low[u] > disc[v])
                low[u] = disc[v];
        }

    if (low[u] == disc[u]) {
        printf("SCC: ");
        while (1) {
            int v = stack[top--];
            inStack[v] = 0;
            printf("%d ", v);
            if (u == v) break;
        }
        printf("\n");
    }
}

void findSCCs() {
    memset(disc, -1, sizeof(disc));
    memset(low, -1, sizeof(low));
    memset(inStack, 0, sizeof(inStack));
    top = -1;

    for (int i = 0; i < n; i++)
        if (disc[i] == -1)
            SCCUtil(i);
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("\n--- Strongly Connected Components ---\n");
    findSCCs();

    printf("\n--- Articulation Points and Bridges ---\n");
    findAPsAndBridges();

    return 0;
}
