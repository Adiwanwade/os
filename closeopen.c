#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    int fd[2];
    char buf1[25] = "just a test \n";
    char buf2[50];
    fd[0] = open("file1.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    fd[1] = open("file2.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd[0] == -1 || fd[1] == -1)
    {
        perror("Open");
        exit(EXIT_FAILURE);
    }
    // Writing to file1.txt
    write(fd[0], buf1, strlen(buf1));
    printf("Enter the text now: ");
    fgets(buf1, sizeof(buf1), stdin);
    write(fd[0], buf1, strlen(buf1));
    // Rewind to the beginning of file1.txt
    lseek(fd[0], 0, SEEK_SET); // Fix: Replace Iseek with lseek
    // Reading from file1.txt
    ssize_t bytes_read = read(fd[0], buf2, sizeof(buf2));
    if (bytes_read == -1)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    // Writing the read data to console
    printf("Data read from file1.txt: %s\n", buf2);

    // Rewind to the beginning of file2.txt
    lseek(fd[1], 0, SEEK_SET); // Fix: Replace Iseek with lseek
    // Reading from file2.txt
    bytes_read = read(fd[1], buf2, sizeof(buf2));
    if (bytes_read == -1)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    // Writing the read data to console
    printf("Data read from file2.txt: %s\n", buf2);
    close(fd[0]);
    close(fd[1]);
    return 0;
}
