#include <stdio.h>

int main() {
    int num = 42;
    int *ptr = &num;
    int **pptr = &ptr;

    printf("Value using single pointer:   %d\n", *ptr);
    printf("Value using double pointer:   %d\n", **pptr);

    return 0;
}
