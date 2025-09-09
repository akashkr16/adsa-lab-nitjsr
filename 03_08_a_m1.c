//Name: Akash Kumar
//Roll No. : 2025PGCSIS09


#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int q1[SIZE], q2[SIZE];
int front1 = -1, rear1 = -1;
int front2 = -1, rear2 = -1;

int isEmpty(int front, int rear) {
    return (front == -1);
}

int isFull(int rear) {
    return (rear == SIZE - 1);
}

void enqueue(int *q, int *front, int *rear, int x) {
    if (isFull(*rear)) {
        printf("Queue Overflow!\n");
        return;
    }
    if (*front == -1) *front = 0;
    q[++(*rear)] = x;
}

int dequeue(int *q, int *front, int *rear) {
    if (isEmpty(*front, *rear)) {
        printf("Queue Underflow!\n");
        return -1;
    }
    int val = q[*front];
    if (*front == *rear) *front = *rear = -1;
    else (*front)++;
    return val;
}

// Stack operations
void push(int x) {
    enqueue(q2, &front2, &rear2, x);
    while (!isEmpty(front1, rear1)) {
        enqueue(q2, &front2, &rear2, dequeue(q1, &front1, &rear1));
    }
    // Swap queues
    int *tq, tf, tr;
    tq = q1; q1[0] = q2[0]; 
    int *tempq = q1; q1 = q2; q2 = tempq;
    int tempFront = front1; front1 = front2; front2 = tempFront;
    int tempRear = rear1; rear1 = rear2; rear2 = tempRear;
    printf("%d pushed\n", x);
}

void pop() {
    if (isEmpty(front1, rear1)) {
        printf("Stack Underflow!\n");
        return;
    }
    printf("%d popped\n", dequeue(q1, &front1, &rear1));
}

void display() {
    if (isEmpty(front1, rear1)) {
        printf("Stack Empty!\n");
        return;
    }
    printf("Stack (top->bottom): ");
    for (int i = front1; i <= rear1; i++) {
        printf("%d ", q1[i]);
    }
    printf("\n");
}

int main() {
    push(10);
    push(20);
    push(30);
    display();
    pop();
    display();
    push(40);
    display();
    return 0;
}
