#include <stdio.h>

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void bucketSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];

    int bucket[10][n], count[10];
    for (int i = 0; i < 10; i++) count[i] = 0;

    for (int i = 0; i < n; i++) {
        int idx = (arr[i] * 10) / (max + 1);
        bucket[idx][count[idx]++] = arr[i];
    }

    int k = 0;
    for (int i = 0; i < 10; i++) {
        insertionSort(bucket[i], count[i]);
        for (int j = 0; j < count[i]; j++) {
            arr[k++] = bucket[i][j];
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

    bucketSort(arr, n);

    printf("Sorted Array (Bucket Sort): ");
    printArray(arr, n);
    return 0;
}
