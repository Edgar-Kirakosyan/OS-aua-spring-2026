#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *firstFilePath = NULL;
    char *secondFilePath = NULL;
    size_t inputLen = 0;

    printf("Enter first file location: ");
    if (getline(&firstFilePath, &inputLen, stdin) == -1) {
        perror("Failed to read first input");
        return 1;
    }

    for (int i = 0; firstFilePath[i] != '\0'; i++) {
        if (firstFilePath[i] == '\n' || firstFilePath[i] == '\r') {
            firstFilePath[i] = '\0';
            break;
        }
    }

    printf("Enter second file location: ");
    inputLen = 0;
    if (getline(&secondFilePath, &inputLen, stdin) == -1) {
        perror("Failed to read second input");
        free(firstFilePath);
        return 1;
    }

    for (int i = 0; secondFilePath[i] != '\0'; i++) {
        if (secondFilePath[i] == '\n' || secondFilePath[i] == '\r') {
            secondFilePath[i] = '\0';
            break;
        }
    }

    int firstFd = open(firstFilePath, O_RDONLY);
    if (firstFd == -1) {
        perror("Failed to open first file");
        free(firstFilePath);
        free(secondFilePath);
        return 1;
    }

    int secondFd = open(secondFilePath, O_RDONLY);
    if (secondFd == -1) {
        perror("Failed to open second file");
        close(firstFd);
        free(firstFilePath);
        free(secondFilePath);
        return 1;
    }

    #define CHUNK_SIZE 512
    char firstBuffer[CHUNK_SIZE];
    char secondBuffer[CHUNK_SIZE];
    off_t currentByteIndex = 0;

    while (1) {
        ssize_t bytesReadFirst = read(firstFd, firstBuffer, CHUNK_SIZE);
        if (bytesReadFirst == -1) {
            perror("Error reading first file");
            close(firstFd);
            close(secondFd);
            free(firstFilePath);
            free(secondFilePath);
            return 1;
        }

        ssize_t bytesReadSecond = read(secondFd, secondBuffer, CHUNK_SIZE);
        if (bytesReadSecond == -1) {
            perror("Error reading second file");
            close(firstFd);
            close(secondFd);
            free(firstFilePath);
            free(secondFilePath);
            return 1;
        }

        ssize_t minBytes = (bytesReadFirst < bytesReadSecond) ? bytesReadFirst : bytesReadSecond;
        
        for (ssize_t i = 0; i < minBytes; i++) {
            if (firstBuffer[i] != secondBuffer[i]) {
                printf("Files differ at byte %ld\n", (long)(currentByteIndex + i));
                close(firstFd);
                close(secondFd);
                free(firstFilePath);
                free(secondFilePath);
                return 2;
            }
        }

        currentByteIndex += minBytes;

        if (bytesReadFirst != bytesReadSecond) {
            printf("Files differ at byte %ld\n", (long)currentByteIndex);
            close(firstFd);
            close(secondFd);
            free(firstFilePath);
            free(secondFilePath);
            return 2;
        }

        if (bytesReadFirst == 0 && bytesReadSecond == 0) {
            break;
        }
    }

    printf("Files are identical\n");
    close(firstFd);
    close(secondFd);
    free(firstFilePath);
    free(secondFilePath);
    return 0;
}
