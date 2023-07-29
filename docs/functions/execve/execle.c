#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    // Count the current environment variables
    int count = 0;
    while (envp[count]) {
        count++;
    }

    // Allocate space for the new environment, including the extra variable
    char **new_environ = malloc((count + 2) * sizeof(char *));
    for (int i = 0; i < count; i++) {
        new_environ[i] = envp[i];
    }

    // Add the custom variable
    new_environ[count] = "VAR=hello";
    new_environ[count + 1] = NULL;

    // Execute the new program with the custom environment
		// int execle(const char *path, const char *arg0, ..., char *const envp[]);

    execle("./my_script.sh", "my_script.sh", NULL, new_environ);
    free(new_environ); // This line is never reached, but it's good practice

    perror("execle"); // Only reached if execle fails
    return 1;
}

