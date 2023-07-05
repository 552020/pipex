#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int file_desc = open("test.txt", O_WRONLY | O_APPEND);

    if (file_desc < 0) { 
        printf("Error opening the file\n");
        return -1; 
    }
	printf("File descriptor: %d\n", file_desc);

    // Using dup to duplicate the file descriptor
    int copy_desc = dup(file_desc); 
	printf("Copy descriptor: %d\n", copy_desc);

    write(copy_desc, "This is a test text", 19);
    write(file_desc, "Hello world!", 12);

    close(file_desc);
    close(copy_desc);

    return 0;
}
