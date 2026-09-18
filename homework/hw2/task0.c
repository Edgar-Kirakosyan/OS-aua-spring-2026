#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid1, pid2, pid3;
    
    pid1 = fork();
    pid2 = fork();
    pid3 = fork();
    
    printf("Process id: %d | Parent process id: %d\n", getpid(), getppid());
    wait(NULL);

    return 0;
}
