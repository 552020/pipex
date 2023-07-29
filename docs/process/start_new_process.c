#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();  // create a new process

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {  // we are in the child process
        execl("/bin/ls", "ls", "-l", NULL);  // replace the current program with /bin/ls

        perror("execl failed");  // execl only returns if there's an error
        return 1;
    } else {  // we are in the parent process
        printf("Child process id: %d\n", pid);
    }

    return 0;
}

