#include <unistd.h>

int main() {
    execl("/bin/ls", "ls", "-l", NULL);
    return 0; // Only reached if execl fails
}

//  int execl(const char *path, const char *arg0, ..., /*, (char *)0, */);
