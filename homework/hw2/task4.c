#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <stdint.h>
#include <sys/wait.h>

int main() {

    int pid1 = fork();
    if(pid1 == 0) {
        execl("/bin/grep", "grep", "main", "test.txt", (char *)NULL);

        //Shouldn't reach this printf if successful.
        printf("The program failed.");
    } 
    waitpid(pid1, NULL, 0);
    printf("Parent process finished.\n");

    return 0;
}
