#include <stdio.h>

int main() {
    char str[] = "Hello";
    char *ptr = str;
    
    printf("String characters: ");
    while (*ptr != '\0') {
        printf("%c", *ptr);
        ptr++;
    }
    printf("\n");
    
    char *start = str;
    char *end = ptr;
    
    int length = end - start;
    printf("Character count: %d\n", length);

    return 0;
}
