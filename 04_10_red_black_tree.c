//Name : Akash Kumar
//Roll No.: 2025PGCSIS09



#include <stdio.h>
#include <stdlib.h>

// Red-Black Tree node colors
enum Color { RED, BLACK };

// Node structure
struct Node {
    int data;
    enum Color color;
    struct Node *left, *right, *parent;
};

// Create new node
struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

// Utility: get grandparent
struct Node* grandparent(struct Node* n) {
    if (n && n->parent) return n->parent->parent;
    return NULL;
}

// Utility: get uncle
struct Node* uncle(struct Node* n) {
    struct Node* g = grandparent(n);
    if (!g) return NULL;
    if (n->parent == g->left) return g->right;
    return g->left;
}

// Left rotate
struct Node* leftRotate(struct Node* root, struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
    return root;
}

// Right rotate
struct Node* rightRotate(struct Node* root, struct Node* x) {
    struct Node* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->right = x;
    x->parent = y;
    return root;
}

// Fix violations after insertion
struct Node* fixInsert(struct Node* root, struct Node* z) {
    while (z->parent && z->parent->color == RED) {
        struct Node* u = uncle(z);
        if (u && u->color == RED) { // Case 1
            z->parent->color = BLACK;
            u->color = BLACK;
            grandparent(z)->color = RED;
            z = grandparent(z);
        } else {
            if (z->parent == grandparent(z)->left) {
                if (z == z->parent->right) { // Case 2
                    z = z->parent;
                    root = leftRotate(root, z);
                }
                // Case 3
                z->parent->color = BLACK;
                grandparent(z)->color = RED;
                root = rightRotate(root, grandparent(z));
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    root = rightRotate(root, z);
                }
                z->parent->color = BLACK;
                grandparent(z)->color = RED;
                root = leftRotate(root, grandparent(z));
            }
        }
    }
    root->color = BLACK;
    return root;
}

// Insert item
struct Node* insertItem(struct Node* root, int data) {
    struct Node* z = createNode(data);
    struct Node* y = NULL;
    struct Node* x = root;

    while (x) {
        y = x;
        if (z->data < x->data) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (!y) root = z;
    else if (z->data < y->data) y->left = z;
    else y->right = z;

    return fixInsert(root, z);
}

// Search item
struct Node* searchItem(struct Node* root, int data) {
    if (!root || root->data == data) return root;
    if (data < root->data) return searchItem(root->left, data);
    return searchItem(root->right, data);
}

// Delete tree
void deleteTree(struct Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// Print preorder
void preorder(struct Node* root) {
    if (root) {
        printf("%d(%s) ", root->data, root->color == RED ? "R" : "B");
        preorder(root->left);
        preorder(root->right);
    }
}



int main() {
    struct Node* root = NULL;

    root = insertItem(root, 10);
    root = insertItem(root, 20);
    root = insertItem(root, 30);
    root = insertItem(root, 15);

    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");

    int key = 15;
    if (searchItem(root, key)) printf("Found %d\n", key);
    else printf("%d Not Found\n", key);

    deleteTree(root);
    return 0;
}
