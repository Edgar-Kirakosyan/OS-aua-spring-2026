#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i;
    int sum = 0;
    double average;
    int *arr;

    printf("Enter n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("n must be greater than 0\n");
        return 1;
    }

    arr = calloc(n, sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Initial values: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("Enter integer %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    printf("Updated values: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        sum = sum + arr[i];
    }
    average = (double) sum / n;

    printf("Average = %.2f\n", average);
    free(arr);

    return 0;
}
