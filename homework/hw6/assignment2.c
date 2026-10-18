// ASSIGNMENT 2 OF HW 6

#include <stdio.h>
//Create a struct in C with the following fields in the given order:
struct variables {
    char a;
    int b;
    double c;
};

struct variablesRearranged {
    double c;
    int b;
    char a;
};

int main() {
    //Use sizeof() to print the size of the struct and print the addresses of each field using the & operator.

    struct variables structType;
    printf("The size of variables struct: %zu\n", sizeof(structType));
    printf("a: %p\n", (void *)&structType.a);
    printf("b: %p\n", (void *)&structType.b);
    printf("c: %p\n", (void *)&structType.c);

    //after rearranging
    printf("Rearranged struct.\n");
    struct variablesRearranged rearrangedStruct;
    printf("The size of variables struct: %zu\n", sizeof(rearrangedStruct));
    printf("c: %p\n", (void *)&rearrangedStruct.c);
    printf("b: %p\n", (void *)&rearrangedStruct.b);
    printf("a: %p\n", (void *)&rearrangedStruct.a); 
    return 0;
}
