#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

int main() {

    int pid1 = fork();
    if(pid1 == 0) {
        pid_t cpid = getpid();
        printf("Child process id: %d\n", cpid);
        exit(0);
    } else {
        pid_t ppid = getpid();
        printf("Parent process id: %d\n", ppid);
    }

    return 0;
}
