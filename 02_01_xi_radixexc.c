#include <stdio.h>

void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0) return;

    int i = left, j = right;
    while (i <= j) {
        while (i <= right && ((arr[i] >> bit) & 1) == 0) i++;
        while (j >= left && ((arr[j] >> bit) & 1) == 1) j--;
        if (i < j) {
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }

    radixExchangeSort(arr, left, j, bit - 1);
    radixExchangeSort(arr, i, right, bit - 1);
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

    int maxBit = sizeof(int) * 8 - 1;  
    radixExchangeSort(arr, 0, n-1, maxBit);

    printf("Sorted Array (Radix Exchange Sort): ");
    printArray(arr, n);
    return 0;
}
