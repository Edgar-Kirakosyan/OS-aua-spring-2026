#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *filePath = NULL;
    size_t len = 0;
    
    printf("Enter source file location: ");
    
    if (getline(&filePath, &len, stdin) == -1) {
        perror("Failed to read input");
        return 1;
    }

    for (int i = 0; filePath[i] != '\0'; i++) {
        if (filePath[i] == '\n' || filePath[i] == '\r') {
            filePath[i] = '\0';
            break;
        }
    }

    int sourceFile = open(filePath, O_RDONLY);
    if(sourceFile == -1) {
        perror("Failed to open the source file");
        free(filePath);
        return 1;
    }

    off_t size = lseek (sourceFile, 0, SEEK_END);
    if (size == (off_t) -1) {
        perror("Lseek failed");
        close(sourceFile);
    }

    printf("demo.txt size is: %ld\n", size);

   if (size > 0) {
        for (off_t i = size - 1; i >= 0; i--) {
            if (lseek(sourceFile, i, SEEK_SET) == (off_t) -1) {
                perror("Lseek failed during reverse read");
                break;
            }

            char c;
            ssize_t bytesRead = read(sourceFile, &c, 1);
            if (bytesRead == 1) {
                write(STDOUT_FILENO, &c, 1);
            } else if (bytesRead == -1) {
                perror("Read failed");
                break;
            }
        }
    }

    write(STDOUT_FILENO, "\n", 1);

    close(sourceFile);
    free(filePath);

    printf("\nThe execution of the application is finished successfully.\n");
    return 0;
}
