#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Opening demo.txt file...\n");
    int fd = open("demo.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fd == -1) {
        perror("Opening demo.txt failed");
        close(fd);
    }
    printf("Successfully opened demo.txt file...\n");

    char buf[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    printf("Writing to the opened demo.txt file...\n");
    ssize_t bufWrite = write(fd, buf, sizeof (buf));
    if(bufWrite == -1) {
        perror("Error while wriitng to the file...");
        close(fd);
    }
    printf("Successfully wrote to the demo.txt file...\n");
    printf("Closing the demo.txt file...\n");
    close(fd);

    printf("Reopeining the demo.txt file...\n");
    fd = open("demo.txt", O_RDWR);
    if(fd == -1) {
        perror("Opening demo.txt failed");
        close(fd);
    }

    off_t ret = lseek (fd, 0, SEEK_END);
    if (ret == (off_t) -1) {
        perror("Lseek failed");
        close(fd);
    }

    printf("demo.txt size is: %ld\n", ret);

    printf("Truncating the file...\n");
    int truncInt = ftruncate(fd, 10);
    if(truncInt == -1) {
        perror("Truncating failed");
        close(fd);
    }
    printf("Successfully truncated the file...\n");

    ret = lseek (fd, 0, SEEK_END);
    if (ret == (off_t) -1) {
        perror("Lseek failed");
        close(fd);
    }

    printf("demo.txt size is: %ld\n", ret);

    ret = lseek (fd, 0, SEEK_SET);
    if (ret == (off_t) -1) {
        perror("Lseek failed");
        close(fd);
    }

    printf("Reading demo.txt file...\n");
    char buffer[256];
    ssize_t bytesRead; 
    ssize_t bytesWritten;

    while (1) {
        bytesRead = read(fd, buffer, sizeof(buffer));
        
        if (bytesRead == -1) {
            perror("Reading failed");
            break;
        }
        
        if (bytesRead == 0) {
            printf("\nEnd of file is reached.\n");
            break;
        }

        bytesWritten = write(1, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Writing failed");
            break;
        }
    }

    close(fd);
    printf("\n\nThe execution of the application has finished.\n");
    return 1;
}
