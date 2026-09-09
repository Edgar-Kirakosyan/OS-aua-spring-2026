#include <stdio.h>

int main() {
    int arrayOfInt[5] = {1, 2, 3, 4, 5};
    int *pointerToArray = arrayOfInt;
    
    for(int i = 0; i < 5; i++) {
        printf("Element of array: %d\n", *pointerToArray);
        *pointerToArray *= 10;
        pointerToArray++;
    }

    pointerToArray = arrayOfInt;
    for(int i = 0; i < 5; i++) {
        printf("Modified element of array using pointer: %d\n", *pointerToArray);
        printf("Modified element of array using array: %d\n", arrayOfInt[i]);
        pointerToArray++;
    }

    return 0;
}
