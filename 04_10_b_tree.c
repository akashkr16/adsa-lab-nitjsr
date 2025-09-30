//Name : Akash Kumar
//Roll No: 2025PGCSIS09

//Implement the functions createTree(), deleteTree(), insertItem(), deleteItem(), serachItem() for AVL 
//trees, i.e. height balanced binary search trees, red-black trees, B Trees and B+ Trees.  

#include <stdio.h>
#include <stdlib.h>

#define T 3  // Minimum degree (defines the range for number of keys)

// B-Tree node
struct BTreeNode {
    int keys[2 * T - 1];
    struct BTreeNode* children[2 * T];
    int n;       // Current number of keys
    int leaf;    // 1 if leaf, 0 otherwise
};

// Create a new B-Tree node
struct BTreeNode* createNode(int leaf) {
    struct BTreeNode* node = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2 * T; i++) node->children[i] = NULL;
    return node;
}

// Traverse
void traverse(struct BTreeNode* root) {
    if (root == NULL) return;
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf) traverse(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf) traverse(root->children[i]);
}

// Search key
struct BTreeNode* searchItem(struct BTreeNode* root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i]) i++;
    if (i < root->n && root->keys[i] == k) return root;
    if (root->leaf) return NULL;
    return searchItem(root->children[i], k);
}

// Split child
void splitChild(struct BTreeNode* parent, int i, struct BTreeNode* y) {
    struct BTreeNode* z = createNode(y->leaf);
    z->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        z->keys[j] = y->keys[j + T];

    if (!y->leaf) {
        for (int j = 0; j < T; j++)
            z->children[j] = y->children[j + T];
    }

    y->n = T - 1;

    for (int j = parent->n; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[i + 1] = z;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = y->keys[T - 1];
    parent->n++;
}

// Insert non-full
void insertNonFull(struct BTreeNode* node, int k) {
    int i = node->n - 1;
    if (node->leaf) {
        while (i >= 0 && k < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = k;
        node->n++;
    } else {
        while (i >= 0 && k < node->keys[i]) i--;
        i++;
        if (node->children[i]->n == 2 * T - 1) {
            splitChild(node, i, node->children[i]);
            if (k > node->keys[i]) i++;
        }
        insertNonFull(node->children[i], k);
    }
}

// Insert
struct BTreeNode* insertItem(struct BTreeNode* root, int k) {
    if (root == NULL) {
        root = createNode(1);
        root->keys[0] = k;
        root->n = 1;
        return root;
    }

    if (root->n == 2 * T - 1) {
        struct BTreeNode* s = createNode(0);
        s->children[0] = root;
        splitChild(s, 0, root);
        int i = 0;
        if (s->keys[0] < k) i++;
        insertNonFull(s->children[i], k);
        return s;
    } else {
        insertNonFull(root, k);
        return root;
    }
}

int main() {
    struct BTreeNode* root = NULL;
    int choice, x;

    while (1) {
        printf("\nB-Tree MENU: 1-Insert 2-Search 3-Traverse 4-Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
            case 1:
                printf("Enter key: ");
                scanf("%d", &x);
                root = insertItem(root, x);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &x);
                printf(searchItem(root, x) ? "Found\n" : "Not Found\n");
                break;
            case 3:
                printf("B-Tree traversal: ");
                traverse(root);
                printf("\n");
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
