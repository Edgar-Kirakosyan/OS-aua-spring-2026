#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <stdint.h>
#include <sys/wait.h>

int main() {

    int forked = fork();
    if(forked == 0) {
        printf("Hello from the child.\n");
        execl("/bin/ls", "ls", (char *)NULL);

        //Shouldn't reach this printf if successful.
        printf("The program failed.");
    } else {
        printf("Hello from the parent.\n");
	wait(NULL);
	printf("parent process done.\n");
    }

    return 0;
}


