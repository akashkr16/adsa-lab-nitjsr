#include <stdio.h>
#include <string.h>

void countingSort(int arr[], int n) {
    int max = arr[0], min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    int range = max - min + 1;
    int count[range], output[n];
    memset(count, 0, sizeof(count));

    for (int i = 0; i < n; i++) count[arr[i] - min]++;
    for (int i = 1; i < range; i++) count[i] += count[i-1];
    for (int i = n-1; i >= 0; i--) {
        output[count[arr[i]-min] - 1] = arr[i];
        count[arr[i]-min]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
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

    countingSort(arr, n);

    printf("Sorted Array (Counting Sort): ");
    printArray(arr, n);
    return 0;
}
