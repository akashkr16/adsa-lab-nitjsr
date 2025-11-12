#include <stdio.h>
#define MAX 20
int n, e, graph[MAX][MAX], m, found=0;
int set[MAX];

int isClique(int size){
    for(int i=0;i<size;i++)
        for(int j=i+1;j<size;j++)
            if(!graph[set[i]][set[j]]) return 0;
    return 1;
}

void findClique(int i, int size){
    if(found) return;
    if(size==m){ if(isClique(m)){ found=1; return; } return; }
    if(i>=n) return;
    set[size]=i;
    findClique(i+1,size+1);
    findClique(i+1,size);
}

int main(){
    printf("Enter vertices and edges: ");
    scanf("%d %d",&n,&e);
    for(int i=0;i<e;i++){ int u,v; scanf("%d %d",&u,&v); graph[u][v]=graph[v][u]=1; }
    printf("Enter size of clique m: "); scanf("%d",&m);
    findClique(0,0);
    if(found) printf("Graph contains a clique of size %d\n",m);
    else printf("No clique of size %d\n",m);
    return 0;
}
