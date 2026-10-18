// ASSIGNMENT 1 OF HW 6

#include <stdio.h>

int main() {
    //Write a C program where you declare variables of the following types: int, char, double, and short.
    int integerType;
    char charType;
    double doubleType;
    short shortType;

    //Use sizeof() to print the size of each data type.
    printf("These are the number of bytes each data type takes.\n");
    printf("int: %zu\n", sizeof(integerType));
    printf("char: %zu\n", sizeof(charType));
    printf("double: %zu\n", sizeof(doubleType));
    printf("short: %zu\n", sizeof(shortType));

    //Print the addresses of each variable using the & operator.
    printf("Address of each type.\n");
    printf("int: %p\n",  (void *)&integerType);
    printf("char: %p\n", (void *)&charType);
    printf("double: %p\n", (void *)&doubleType);
    printf("short: %p\n", (void *)&shortType);
    return 0;
}
