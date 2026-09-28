#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    int *arr;
    int *temp;

    arr = malloc(10 * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (i = 0; i < 10; i++) {
        printf("Enter integer %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    temp = realloc(arr, 5 * sizeof(int));
    if (temp == NULL) {
        printf("Memory reallocation failed\n");
        free(arr);
        return 1;
    }
    arr = temp;

    printf("First 5 values: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);

    return 0;
}
