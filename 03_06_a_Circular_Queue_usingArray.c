//Name: Akash Kumar
//Roll No. : 2025PGCSIS09
//Implement a circular queue using (a) an array


#include <stdio.h>
#define SIZE 5

int cq[SIZE];
int front = -1, rear = -1;

int isFull() {
    return (front == (rear + 1) % SIZE);
}

int isEmpty() {
    return (front == -1);
}

void enqueue(int val) {
    if (isFull()) {
        printf("Queue Overflow!\n");
        return;
    }
    if (front == -1) front = 0;
    rear = (rear + 1) % SIZE;
    cq[rear] = val;
    printf("%d enqueued\n", val);
}

void dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow!\n");
        return;
    }
    printf("%d dequeued\n", cq[front]);
    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % SIZE;
}

void display() {
    if (isEmpty()) {
        printf("Queue Empty!\n");
        return;
    }
    int i = front;
    printf("Queue: ");
    while (1) {
        printf("%d ", cq[i]);
        if (i == rear) break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    display();
    dequeue();
    dequeue();
    display();
    enqueue(50);
    enqueue(60);
    display();
    return 0;
}
