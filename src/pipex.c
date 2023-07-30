#include <stdio.h>
#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	int fildes[2];
	pid_t pid;
	if (argc != 5)
	{
		ft_putstr_fd("No, no, no!\n", 2);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
	}
	else
	{
		if(pipe(fildes) == -1)
		{
			ft_putstr_fd("Pipe error!\n", 2);
			return (1);
		}
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("Fork error!\n", 2);
			return (1);
		}
		if (pid == 0)
			execute_cmd1(argv[1], argv[2], envp, fildes);
		wait(NULL);
		execute_cmd2(argv[4], argv[3], envp, fildes);
	}
	return (0);
}
