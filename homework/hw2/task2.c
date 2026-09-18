#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <stdint.h>
#include <sys/wait.h>

int main() {

    int pid1 = fork();
    if(pid1 == 0) {
        printf("Hello from the child.\n");
        execl("/bin/ls", "ls", (char *)NULL);

        //Shouldn't reach this printf if successful.
        printf("The program failed.");
    } 
    waitpid(pid1, NULL, 0);
    int pid2 = fork();
    if(pid2 == 0) {
        printf("Hello from the second child.\n");
        execl("/bin/date", "date", (char *)NULL);

        //Shouldn't reach this printf if successful.
        printf("The program failed.");
    }
    waitpid(pid2, NULL, 0);
    printf("Hello from the parent.\n");

    return 0;
}
