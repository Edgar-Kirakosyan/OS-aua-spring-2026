// ASSIGNMENT 3 OF HW 6

#include <stdio.h>

struct variables {
    char a;
    int b;
    double c;
};

#pragma pack(1)
struct variables2 {
    char a;
    int b;
    double c;
};

int main() {
    struct variables structType;
    printf("The size of variables struct: %zu\n", sizeof(structType));
    printf("a: %p\n", (void *)&structType.a);
    printf("b: %p\n", (void *)&structType.b);
    printf("c: %p\n", (void *)&structType.c);

    //after rearranging
    printf("\n\nAfter pragma pack.\n");
    struct variables2 pragmaStruct;
    printf("The size of variables struct: %zu\n", sizeof(pragmaStruct));
    printf("a: %p\n", (void *)&pragmaStruct.a);
    printf("b: %p\n", (void *)&pragmaStruct.b);
    printf("c: %p\n", (void *)&pragmaStruct.c); 
     
    return 0;
}
