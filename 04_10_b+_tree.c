//Name : Akash Kumar
//Roll No: 2025PGCSIS09

//Implement the functions createTree(), deleteTree(), insertItem(), deleteItem(), serachItem() for AVL 
//trees, i.e. height balanced binary search trees, red-black trees, B Trees and B+ Trees.  



#include <stdio.h>
#include <stdlib.h>

#define ORDER 3   // B+ Tree order (max keys in internal = ORDER-1)

// Node structure
struct BPTreeNode {
    int keys[ORDER];
    struct BPTreeNode* children[ORDER + 1];
    int isLeaf;
    int n; // number of keys
    struct BPTreeNode* next; // used only for leaves
};

// Create a new node
struct BPTreeNode* createNode(int isLeaf) {
    struct BPTreeNode* node = (struct BPTreeNode*)malloc(sizeof(struct BPTreeNode));
    node->isLeaf = isLeaf;
    node->n = 0;
    node->next = NULL;
    for (int i = 0; i <= ORDER; i++) node->children[i] = NULL;
    return node;
}

// Search in B+ Tree
struct BPTreeNode* searchItem(struct BPTreeNode* root, int key) {
    if (root == NULL) return NULL;
    struct BPTreeNode* cursor = root;
    while (!cursor->isLeaf) {
        int i = 0;
        while (i < cursor->n && key >= cursor->keys[i]) i++;
        cursor = cursor->children[i];
    }
    for (int i = 0; i < cursor->n; i++)
        if (cursor->keys[i] == key) return cursor;
    return NULL;
}

// Traverse (print all keys from leaves)
void traverse(struct BPTreeNode* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    struct BPTreeNode* cursor = root;
    while (!cursor->isLeaf) cursor = cursor->children[0]; // go to leftmost leaf
    while (cursor) {
        for (int i = 0; i < cursor->n; i++) printf("%d ", cursor->keys[i]);
        cursor = cursor->next;
    }
    printf("\n");
}

// Insert into leaf node
void insertLeaf(struct BPTreeNode* leaf, int key) {
    int i = leaf->n - 1;
    while (i >= 0 && leaf->keys[i] > key) {
        leaf->keys[i + 1] = leaf->keys[i];
        i--;
    }
    leaf->keys[i + 1] = key;
    leaf->n++;
}

// Split leaf node
struct BPTreeNode* splitLeaf(struct BPTreeNode* leaf, int* newKey) {
    int mid = (ORDER + 1) / 2;
    struct BPTreeNode* newLeaf = createNode(1);
    newLeaf->n = leaf->n - mid;

    for (int i = 0; i < newLeaf->n; i++)
        newLeaf->keys[i] = leaf->keys[mid + i];

    leaf->n = mid;
    newLeaf->next = leaf->next;
    leaf->next = newLeaf;
    *newKey = newLeaf->keys[0];
    return newLeaf;
}

// Insert into B+ Tree (simplified, handles only root splits)
struct BPTreeNode* insertItem(struct BPTreeNode* root, int key) {
    if (root == NULL) {
        root = createNode(1); // leaf root
        root->keys[0] = key;
        root->n = 1;
        return root;
    }

    struct BPTreeNode* cursor = root;
    struct BPTreeNode* parent = NULL;

    while (!cursor->isLeaf) {
        parent = cursor;
        int i = 0;
        while (i < cursor->n && key >= cursor->keys[i]) i++;
        cursor = cursor->children[i];
    }

    insertLeaf(cursor, key);

    if (cursor->n == ORDER) {
        int newKey;
        struct BPTreeNode* newLeaf = splitLeaf(cursor, &newKey);

        if (cursor == root) {
            struct BPTreeNode* newRoot = createNode(0);
            newRoot->keys[0] = newKey;
            newRoot->children[0] = cursor;
            newRoot->children[1] = newLeaf;
            newRoot->n = 1;
            root = newRoot;
        } else {
            // For simplicity, not implementing multi-level splits
            printf("Split beyond root not implemented in this short demo.\n");
        }
    }
    return root;
}

int main() {
    struct BPTreeNode* root = NULL;
    int choice, x;

    while (1) {
        printf("\nB+ Tree MENU: 1-Insert 2-Search 3-Traverse 4-Exit\nChoice: ");
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
                printf("B+ Tree traversal (leaves): ");
                traverse(root);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

