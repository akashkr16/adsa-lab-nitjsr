#include <stdio.h>

int n, W;
int weights[20], values[20];
int maxProfit = 0;

void knapsackBT(int i, int currWeight, int currProfit) {
    if (i == n) {
        if (currProfit > maxProfit)
            maxProfit = currProfit;
        return;
    }

    // Include the item if possible
    if (currWeight + weights[i] <= W)
        knapsackBT(i + 1, currWeight + weights[i], currProfit + values[i]);

    // Exclude the item
    knapsackBT(i + 1, currWeight, currProfit);
}

int main() {
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter weights: ");
    for (int i = 0; i < n; i++) scanf("%d", &weights[i]);
    printf("Enter values: ");
    for (int i = 0; i < n; i++) scanf("%d", &values[i]);
    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    knapsackBT(0, 0, 0);

    printf("Maximum value in Knapsack (Backtracking) = %d\n", maxProfit);
    return 0;
}
