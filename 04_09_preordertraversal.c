//Name: Akash Kumar
//Roll No: 2025PGCSIS09



#include <stdio.h>
#include <stdlib.h>

// Structure for a tree node
struct Node {
    int data;
    struct Node *left, *right;
};

// Stack structure
struct Stack {
    struct Node* arr[100];
    int top;
};

// Utility to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Stack functions
void push(struct Stack* s, struct Node* node) {
    s->arr[++s->top] = node;
}
struct Node* pop(struct Stack* s) {
    return s->arr[s->top--];
}
int isEmpty(struct Stack* s) {
    return s->top == -1;
}

// Iterative preorder traversal
void preorder(struct Node* root) {
    if (root == NULL) return;

    struct Stack s;
    s.top = -1;
    push(&s, root);

    while (!isEmpty(&s)) {
        struct Node* node = pop(&s);
        printf("%d ", node->data);

        if (node->right) push(&s, node->right); // right first
        if (node->left) push(&s, node->left);   // left second
    }
}

int main() {
    // Example tree:
    //        1
    //      /   \
    //     2     3
    //    / \   / \
    //   4   5 6   7

    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    printf("Preorder Traversal (Iterative): ");
    preorder(root);

    return 0;
}
