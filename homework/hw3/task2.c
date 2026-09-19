#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t pid1 = fork();
    if (pid1 == 0) {
        printf("Child 1 process id: %d\n", getpid());
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        printf("Child 2 process id: %d\n", getpid());
        exit(0);
    }

    printf("Parent process id: %d\n", getpid());

    int status1;
    pid_t child1 = wait(&status1);
    printf("Waited for child %d, status %d\n", child1, status1);

    int status2;
    pid_t child2 = waitpid(pid2, &status2, 0);
    printf("Waited for child %d, status %d\n", child2, status2);

    return 0;
}
