#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    char **arr;
    char **temp;

    arr = malloc(3 * sizeof(char *));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (i = 0; i < 3; i++) {
        arr[i] = (char *) malloc(51 * sizeof(char));
        if (arr[i] == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
    }

    for (i = 0; i < 3; i++) {
        printf("Enter string %d: ", i + 1);
        scanf("%50s", arr[i]);
    }

    printf("\nThe 3 strings:\n");
    for (i = 0; i < 3; i++) {
        printf("%s\n", arr[i]);
    }

    temp = realloc(arr, 5 * sizeof(char *));
    if (temp == NULL) {
        printf("Memory reallocation failed\n");
        for (i = 0; i < 3; i++) {
            free(arr[i]);
        }
        free(arr);
        return 1;
    }
    arr = temp;

    for (i = 3; i < 5; i++) {
        arr[i] = malloc(51 * sizeof(char));
        if (arr[i] == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
    }

    printf("\n");
    for (i = 3; i < 5; i++) {
        printf("Enter string %d: ", i + 1);
        scanf("%50s", arr[i]);
    }

    printf("\nAll 5 strings:\n");
    for (i = 0; i < 5; i++) {
        printf("%s\n", arr[i]);
    }
    
    for (i = 0; i < 5; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
