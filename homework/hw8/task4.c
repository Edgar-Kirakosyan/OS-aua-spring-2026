#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *filename = "log.txt";
    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("Failed to open log.txt");
        return 1;
    }

    char input_buf[1024];
    ssize_t bytes_read = read(0, input_buf, sizeof(input_buf) - 1);
    if (bytes_read == -1) {
        perror("Failed to read from stdin");
        close(fd);
        return 1;
    }
    
    if (bytes_read > 0 && input_buf[bytes_read - 1] == '\n') {
        input_buf[bytes_read - 1] = '\0';
        bytes_read--;
    } else {
        input_buf[bytes_read] = '\0';
    }

    pid_t pid = getpid();
    char final_buf[2048];
    int formatted_len = snprintf(final_buf, sizeof(final_buf), "PID=%d: %s\n", pid, input_buf);
    if (formatted_len < 0) {
        perror("Formatting failed");
        close(fd);
        return 1;
    }

    ssize_t bytes_written = write(fd, final_buf, formatted_len);
    if (bytes_written == -1) {
        perror("Writing to log.txt failed");
        close(fd);
        return 1;
    }

    /* 
     * Even though O_APPEND forces the kernel to atomically reposition the file 
     * offset to the end of the file immediately before every write operation, 
     * the open file description also maintains its own current file offset pointer. 
     * When a write completes successfully, the kernel updates this internal 
     * offset to reflect the new end-of-file position. Therefore, querying 
     * lseek(fd, 0, SEEK_CUR) right after a write will return that updated 
     * current offset position.
     */
    off_t current_offset = lseek(fd, 0, SEEK_CUR);
    if (current_offset == (off_t)-1) {
        perror("lseek failed");
        close(fd);
        return 1;
    }

    printf("Successfully wrote to log.txt. Current file offset (SEEK_CUR): %ld\n", current_offset);
    close(fd);
    return 0;
}
