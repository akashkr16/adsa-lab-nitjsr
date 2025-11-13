#include <stdio.h>
#define MAX 20
int n, graph[MAX][MAX], path[MAX];

int isSafe(int v, int pos){
    if(!graph[path[pos-1]][v]) return 0;
    for(int i=0;i<pos;i++) if(path[i]==v) return 0;
    return 1;
}

int hamiltonianUtil(int pos){
    if(pos==n && graph[path[pos-1]][path[0]]) return 1;
    for(int v=1;v<n;v++){
        if(isSafe(v,pos)){
            path[pos]=v;
            if(hamiltonianUtil(pos+1)) return 1;
            path[pos]=-1;
        }
    }
    return 0;
}

int main(){
    printf("Enter vertices: ");
    scanf("%d",&n);
    printf("Enter adjacency matrix:\n");
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) scanf("%d",&graph[i][j]);
    for(int i=0;i<n;i++) path[i]=-1;
    path[0]=0;
    if(hamiltonianUtil(1)){ printf("Hamiltonian Cycle exists.\n"); }
    else printf("No Hamiltonian Cycle.\n");
    return 0;
}
