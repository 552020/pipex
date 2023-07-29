#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int file_desc = open("output.txt", O_WRONLY | O_CREAT, 0644);

    if (file_desc < 0) { 
        printf("Error opening the file\n");
        return -1; 
    }

    // Backup stdout file descriptor
    int stdout_backup = dup(STDOUT_FILENO);

    // Redirect stdout to file_desc
    dup2(file_desc, STDOUT_FILENO);

    printf("This will be written to the file\n");

    // Restoring the original stdout
    dup2(stdout_backup, STDOUT_FILENO);

    printf("This will be written to the console\n");

    close(file_desc);
    close(stdout_backup);

    return 0;
}
