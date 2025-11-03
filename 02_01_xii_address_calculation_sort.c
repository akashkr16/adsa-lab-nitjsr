#include <stdio.h>
#include <string.h>

void addressCalculationSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];

    int hash[max+1];
    memset(hash, 0, sizeof(hash));

    for (int i = 0; i < n; i++) hash[arr[i]]++;

    int k = 0;
    for (int i = 0; i <= max; i++) {
        while (hash[i] > 0) {
            arr[k++] = i;
            hash[i]--;
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

    addressCalculationSort(arr, n);

    printf("Sorted Array (Address Calculation Sort): ");
    printArray(arr, n);
    return 0;
}
