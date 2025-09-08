//Name: Akash Kumar
//Roll No. : 2025PGCSIS09

//Implement a circular queue using (a) an array (b) a linked list.
//(b)

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int stack1[SIZE], stack2[SIZE];
int top1 = -1, top2 = -1;

void push1(int x) { stack1[++top1] = x; }
int pop1() { return stack1[top1--]; }
void push2(int x) { stack2[++top2] = x; }
int pop2() { return stack2[top2--]; }
int isEmpty1() { return top1 == -1; }
int isEmpty2() { return top2 == -1; }

void enqueue(int x) {
    while (!isEmpty1()) push2(pop1());
    push1(x);
    while (!isEmpty2()) push1(pop2());
    printf("%d enqueued\n", x);
}

void dequeue() {
    if (isEmpty1()) {
        printf("Queue Underflow!\n");
        return;
    }
    printf("%d dequeued\n", pop1());
}

void display() {
    if (isEmpty1()) {
        printf("Queue Empty!\n");
        return;
    }
    printf("Queue: ");
    for (int i = 0; i <= top1; i++)
        printf("%d ", stack1[i]);
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
