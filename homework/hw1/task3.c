#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int a = 5;
    int b = 7;
    printf("Old values\n");
    printf("a: %d\n", a);
    printf("b: %d\n", b);
    swap(&a, &b);
    printf("New values\n");
    printf("a: %d\n", a);
    printf("b: %d\n", b);
    return 0;
}
