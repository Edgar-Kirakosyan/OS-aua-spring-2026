#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *filename = "sparse.bin";

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to open sparse.bin for writing");
        return 1;
    }

    const char *start_str = "START";
    ssize_t written = write(fd, start_str, strlen(start_str));
    if (written == -1) {
        perror("Failed to write START");
        close(fd);
        return 1;
    }

    off_t seek_res = lseek(fd, 1024 * 1024, SEEK_CUR);
    if (seek_res == (off_t)-1) {
        perror("lseek forward failed");
        close(fd);
        return 1;
    }

    const char *end_str = "END";
    written = write(fd, end_str, strlen(end_str));
    if (written == -1) {
        perror("Failed to write END");
        close(fd);
        return 1;
    }

    close(fd);

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open sparse.bin for reading");
        return 1;
    }

    off_t apparent_size = lseek(fd, 0, SEEK_END);
    if (apparent_size == (off_t)-1) {
        perror("lseek to end failed");
        close(fd);
        return 1;
    }

    printf("Apparent file size is: %ld bytes\n", apparent_size);

    /*
     * A sparse file creates a "hole" where we skipped forward using lseek 
     * without actually writing any data. The file system does not allocate 
     * physical disk blocks for these empty gaps; it only records metadata 
     * indicating that a gap exists. Therefore, the actual disk usage
     * only accounts for the metadata and the 
     * actual written bytes ("START" and "END"), while the apparent size 
     * includes the full 1 MiB skipped region.
     */

    close(fd);
    return 0;
}
