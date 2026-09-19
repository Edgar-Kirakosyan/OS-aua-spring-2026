#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int child1 = fork();
    int status1;
    if(child1 == 0) {
        printf("I am a child that is about to become an orphan.\n");
        while(1);
    } else {
        printf("I am about to leave my child.\n");
   	wait(NULL);
    }
    
    return 0;
}
