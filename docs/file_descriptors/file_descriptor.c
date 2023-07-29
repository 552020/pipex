#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open a file for writing
    int fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    
    // Print the process ID
    printf("Process ID: %d\n", getpid());
    
    // Sleep for a while to give us a chance to check the open file
    sleep(600);

    close(fd);
    return 0;
}

