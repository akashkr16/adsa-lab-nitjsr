//Name : Akash Kumar
//Roll No. : 2025PGCSIS09

//Implement a circular queue using (b) a linked list.

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *front = NULL, *rear = NULL;

int isEmpty() {
    return front == NULL;
}

void enqueue(int val) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    if (front == NULL) {
        front = rear = newNode;
        rear->next = front;
    } else {
        rear->next = newNode;
        rear = newNode;
        rear->next = front;
    }
    printf("%d enqueued\n", val);
}

void dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow!\n");
        return;
    }
    int val = front->data;
    if (front == rear) {
        free(front);
        front = rear = NULL;
    } else {
        struct Node *temp = front;
        front = front->next;
        rear->next = front;
        free(temp);
    }
    printf("%d dequeued\n", val);
}

void display() {
    if (isEmpty()) {
        printf("Queue Empty!\n");
        return;
    }
    struct Node *temp = front;
    printf("Queue: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != front);
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();
    dequeue();
    display();
    enqueue(40);
    display();
    return 0;
}
