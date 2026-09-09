#include <stdio.h>

int main() {
    int var = 5;
    int *pointerToVar = &var;
    
    printf("Address using variable: %p\n", &var);
    printf("Address using pointer:  %p\n", pointerToVar);

    *pointerToVar = 10;

    printf("Modified var value:     %d\n", var);

    return 0;
}
