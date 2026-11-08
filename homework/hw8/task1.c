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

    // Opening the source file using the given location.
    int sourceFile = open(filePath, O_RDONLY);
    if(sourceFile == -1) {
        perror("Failed to open the source file");
        free(filePath);
        return 1;
    }

    // Free the old path memory before reusing the pointer for getline
    free(filePath);
    filePath = NULL;
    len = 0;

    printf("Enter destination file location: ");
    
    if (getline(&filePath, &len, stdin) == -1) {
        perror("Failed to read input");
        close(sourceFile);
        return 1;
    }

    for (int i = 0; filePath[i] != '\0'; i++) {
        if (filePath[i] == '\n' || filePath[i] == '\r') {
            filePath[i] = '\0';
            break;
        }
    }

    // Opening the destination file using the given location.
    int destinationFile = open(filePath, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
    if(destinationFile == -1) {
        perror("Failed to open/create destination file");
        close(sourceFile);
        free(filePath);
        return 1;
    }

    char buffer[256];
    ssize_t bytesRead; 
    ssize_t bytesWritten;

    while (1) {
        bytesRead = read(sourceFile, buffer, sizeof(buffer));
        
        if (bytesRead == -1) {
            perror("Reading failed");
            break;
        }
        
        if (bytesRead == 0) {
            printf("End of file is reached.\n");
            break;
        }

        bytesWritten = write(destinationFile, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Writing failed");
            break;
        }
    }

    printf("File copied successfully!\n");


    close(sourceFile);
    close(destinationFile);
    free(filePath);

    return 0;
}
