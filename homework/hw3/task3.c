#include <stdio.h>
#include <stdlib.h>

void close() {
    printf("This should be printed before the end of the process.");
    exit(0); // doesn't affect this case.
}


int main() {
    //exit(0); //shouldn't do anything.
    atexit(close);

    printf("This should be printed first.\n");
    //exit(0); // doesn't affect this case.
    return 0;
}
