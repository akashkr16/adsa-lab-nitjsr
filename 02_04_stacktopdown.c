#include <stdio.h>
#include <stdlib.h>

// Structure to represent stack frame
typedef struct {
    int left, right, state;
} Frame;

// Merge function
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSortStack(int arr[], int n) {
    Frame stack[100];
    int top = -1;

    // Push initial range
    stack[++top] = (Frame){0, n - 1, 0};

    while (top >= 0) {
        Frame *cur = &stack[top];

        if (cur->left >= cur->right) { // base case
            top--;
            continue;
        }

        if (cur->state == 0) { // divide left
            int mid = (cur->left + cur->right) / 2;
            cur->state = 1;
            stack[++top] = (Frame){cur->left, mid, 0};
        } 
        else if (cur->state == 1) { // divide right
            int mid = (cur->left + cur->right) / 2;
            cur->state = 2;
            stack[++top] = (Frame){mid + 1, cur->right, 0};
        } 
        else { // conquer (merge)
            int mid = (cur->left + cur->right) / 2;
            merge(arr, cur->left, mid, cur->right);
            top--;
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    printf("Original Array: ");
    printArray(arr, n);

    mergeSortStack(arr, n);

    printf("Sorted Array (Merge Sort with Stack): ");
    printArray(arr, n);

    return 0;
}
