#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i;
    int sum = 0;
    int *arr;

    printf("Enter n: ");
    scanf("%d", &n);

    arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter integer %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    for (i = 0; i < n; i++) {
        sum = sum + arr[i];
    }

    printf("Sum = %d\n", sum);
    free(arr);

    return 0;
}
