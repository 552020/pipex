#include <stdio.h>
#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	int fildes[2];
	pid_t pid;
	if (argc != 5)
		exit_with_error("No, no, no!\nUsage: ./pipex file1 cmd1 cmd2 file2\n", false);
	else
	{
		if(pipe(fildes) == -1)
			exit_with_error("Pipe error!\n", false);
		pid = fork();
		if (pid == -1)
			exit_with_error("Fork error!\n", true);
		if (pid == 0)
			execute_cmd1(argv[1], argv[2], envp, fildes);
		wait(NULL);
		execute_cmd2(argv[4], argv[3], envp, fildes);
	}
	return (0);
}
