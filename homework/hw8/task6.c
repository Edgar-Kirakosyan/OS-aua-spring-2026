#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *filename = "numbers.txt";

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to open numbers.txt for writing");
        return 1;
    }

    for (int i = 1; i <= 10; i++) {
        char line[16];
        int len = snprintf(line, sizeof(line), "%d\n", i);
        if (write(fd, line, len) != len) {
            perror("Failed to write");
            close(fd);
            return 1;
        }
    }
    close(fd);

    fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Failed to reopen numbers.txt");
        return 1;
    }

    off_t line4_offset = 0;
    int newline_count = 0;
    char c;

    while (read(fd, &c, 1) > 0) {
        if (c == '\n') {
            newline_count++;
            if (newline_count == 3) {
                line4_offset = lseek(fd, 0, SEEK_CUR);
                break;
            }
        }
    }

    if (lseek(fd, line4_offset, SEEK_SET) == (off_t)-1) {
        perror("lseek to start of line 4 failed");
        close(fd);
        return 1;
    }

    off_t line4_end_offset = line4_offset;
    char temp_c;
    while (read(fd, &temp_c, 1) > 0) {
        line4_end_offset++;
        if (temp_c == '\n') {
            break;
        }
    }

    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == (off_t)-1) {
        perror("lseek to end failed");
        close(fd);
        return 1;
    }

    off_t rem_size = file_size - line4_end_offset;
    char *remainder = NULL;

    if (rem_size > 0) {
        remainder = malloc(rem_size);
        if (!remainder) {
            perror("Memory allocation failed");
            close(fd);
            return 1;
        }

        if (lseek(fd, line4_end_offset, SEEK_SET) == (off_t)-1) {
            perror("lseek to remainder failed");
            free(remainder);
            close(fd);
            return 1;
        }

        ssize_t bytes_read = read(fd, remainder, rem_size);
        if (bytes_read != rem_size) {
            perror("Failed to read remainder");
            free(remainder);
            close(fd);
            return 1;
        }
    }

    if (lseek(fd, line4_offset, SEEK_SET) == (off_t)-1) {
        perror("lseek back to line 4 failed");
        free(remainder);
        close(fd);
        return 1;
    }

    const char *new_val = "100\n";
    size_t new_val_len = strlen(new_val);
    if (write(fd, new_val, new_val_len) != (ssize_t)new_val_len) {
        perror("Failed to write new line value");
        free(remainder);
        close(fd);
        return 1;
    }

    if (rem_size > 0 && remainder != NULL) {
        if (write(fd, remainder, rem_size) != rem_size) {
            perror("Failed to write remainder back");
            free(remainder);
            close(fd);
            return 1;
        }
        free(remainder);
    }

    close(fd);

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open for verification");
        return 1;
    }

    printf("Final File content\n");
    char print_buf[256];
    ssize_t n;
    while ((n = read(fd, print_buf, sizeof(print_buf))) > 0) {
        write(STDOUT_FILENO, print_buf, n);
    }
    printf("\n");
    close(fd);
    return 0;
}
