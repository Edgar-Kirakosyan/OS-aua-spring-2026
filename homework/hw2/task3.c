#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <stdint.h>
#include <sys/wait.h>

int main() {

    int pid1 = fork();
    if(pid1 == 0) {
        execl("/bin/echo", "echo", "Hello from the child process", (char *)NULL);

        //Shouldn't reach this printf if successful.
        printf("The program failed.");
    } 
    waitpid(pid1, NULL, 0);
    printf("Hello from the parent.\n");

    return 0;
}
