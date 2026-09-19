#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    int child1 = fork();
    int status1;
    if(child1 == 0) {
        exit(0);
    } else {
        int child2 = fork();
        int status2;
        if(child2 == 0) {
            exit(1);
        } else {
            waitpid(child1, &status1, 0);
            waitpid(child2, &status2, 0);
            
            printf("Child1 exit code: %d\n", WEXITSTATUS(status1));
            if(WEXITSTATUS(status1) == 0) {
                printf("Child1 exited normally\n");
            } else {
                printf("Child1 exited with an error\n");
            }

            printf("Child2 exit code: %d\n", WEXITSTATUS(status2));
            if(WEXITSTATUS(status2) == 0) {
                printf("Child2 exited normally\n");
            } else {
                printf("Child2 exited with an error\n");
            }
        }
    }
    
    return 0;
}
