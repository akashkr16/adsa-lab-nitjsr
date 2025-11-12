#include <stdio.h>
#include <string.h>
#define MAX 100

int n, graph[MAX][MAX];
int timeD, disc[MAX], low[MAX], parent[MAX], ap[MAX];
int stack[MAX], top=-1, inStack[MAX];

// ----- Tarjan's for SCC -----
void SCCUtil(int u) {
    static int t=0;
    disc[u]=low[u]=++t;
    stack[++top]=u; inStack[u]=1;
    for(int v=0;v<n;v++) if(graph[u][v]) {
        if(disc[v]==-1) { SCCUtil(v); if(low[u]>low[v]) low[u]=low[v]; }
        else if(inStack[v] && low[u]>disc[v]) low[u]=disc[v];
    }
    if(low[u]==disc[u]) {
        printf("SCC: ");
        while(1) {
            int w=stack[top--]; inStack[w]=0;
            printf("%d ",w);
            if(w==u) break;
        }
        printf("\n");
    }
}

void findSCC() {
    memset(disc,-1,sizeof(disc)); memset(low,-1,sizeof(low)); memset(inStack,0,sizeof(inStack)); top=-1;
    for(int i=0;i<n;i++) if(disc[i]==-1) SCCUtil(i);
}

// ----- Articulation Points & Bridges -----
void DFS_AP_Bridge(int u) {
    static int t=0; disc[u]=low[u]=++t;
    int children=0;
    for(int v=0;v<n;v++) if(graph[u][v]) {
        if(disc[v]==-1) {
            parent[v]=u; children++;
            DFS_AP_Bridge(v);
            if(low[u]>low[v]) low[u]=low[v];
            if(parent[u]==-1 && children>1) ap[u]=1;
            if(parent[u]!=-1 && low[v]>=disc[u]) ap[u]=1;
            if(low[v]>disc[u]) printf("Bridge: %d - %d\n",u,v);
        } else if(v!=parent[u] && low[u]>disc[v]) low[u]=disc[v];
    }
}

void findAP_Bridges() {
    memset(disc,-1,sizeof(disc)); memset(low,-1,sizeof(low)); memset(parent,-1,sizeof(parent)); memset(ap,0,sizeof(ap));
    for(int i=0;i<n;i++) if(disc[i]==-1) DFS_AP_Bridge(i);
    printf("Articulation Points: ");
    for(int i=0;i<n;i++) if(ap[i]) printf("%d ",i);
    printf("\n");
}

int main(){
    printf("Enter number of vertices: ");
    scanf("%d",&n);
    printf("Enter adjacency matrix:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d",&graph[i][j]);

    printf("\nStrongly Connected Components:\n");
    findSCC();

    printf("\nArticulation Points and Bridges:\n");
    findAP_Bridges();
    return 0;
}
