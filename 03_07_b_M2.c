//Name : Akash Kumar
//Roll No. : 2025PGCSIS09
//Implement a queue using two stacks by Methods-2


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
    push1(x);
    printf("%d enqueued\n", x);
}

void dequeue() {
    if (isEmpty1() && isEmpty2()) {
        printf("Queue Underflow!\n");
        return;
    }
    if (isEmpty2()) {
        while (!isEmpty1()) push2(pop1());
    }
    printf("%d dequeued\n", pop2());
}

void display() {
    if (isEmpty1() && isEmpty2()) {
        printf("Queue Empty!\n");
        return;
    }
    printf("Queue: ");
    for (int i = 0; i <= top2; i++) printf("%d ", stack2[i]);
    for (int i = top1; i >= 0; i--) printf("%d ", stack1[i]);
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
