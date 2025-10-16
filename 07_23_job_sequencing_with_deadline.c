#include <stdio.h>

typedef struct {
    char id;
    int deadline, profit;
} Job;

void jobSequencing(Job jobs[], int n){
    int result[n], slot[n];
    for(int i=0;i<n;i++) slot[i] = 0;

    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(jobs[j].profit > jobs[i].profit){
                Job temp = jobs[i]; jobs[i] = jobs[j]; jobs[j] = temp;
            }

    for(int i=0;i<n;i++){
        for(int j=jobs[i].deadline-1;j>=0;j--){
            if(slot[j]==0){
                result[j]=i;
                slot[j]=1;
                break;
            }
        }
    }

    printf("Job sequence: ");
    for(int i=0;i<n;i++)
        if(slot[i]) printf("%c ", jobs[result[i]].id);
    printf("\n");
}

int main(){
    Job jobs[] = {{'A',2,100}, {'B',1,19}, {'C',2,27}, {'D',1,25}, {'E',3,15}};
    int n = 5;
    jobSequencing(jobs, n);
    return 0;
}
