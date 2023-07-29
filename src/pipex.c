#include <stdio.h>
#include "pipex.h"

void execute_cmd1(char *file1, char *cmd1, char **envp, int *fildes)
{
	char *path;
	char **cmd1_args;
	int fd;
	// we close the read end of the pipe cause we are not going to use it
	close(fildes[0]);
	// we open the file1 
	fd = open(file1, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("File1 error!\n", 2);
		exit(1);
	}
	// we redirect the stdin to the file1 so that the cmd1 can read from it
	dup2(fd, STDIN_FILENO);
	// we redirect the stdout to the write end of the pipe so that the cmd2 can read from it
	dup2(fildes[1], STDOUT_FILENO);
	// 
	close(fildes[1]);
	path = find_path(cmd1, envp);
	if (path == NULL)
	{
		ft_putstr_fd("Command not found!\n", 2);
		exit(1);
	}
	cmd1_args = ft_split(cmd1, ' ');
	execve(path, cmd1_args, envp);
}



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
			//TODO: enhnace error message using perror
			ft_putstr_fd("Pipe error!\n", 2);
			return (1);
		}
		pid = fork();
		if (pid == -1)
		{
			//TODO: enhnace error message using perror
			ft_putstr_fd("Fork error!\n", 2);
			return (1);
		}
		if (pid == 0)
		{
			// this was  child process
			execute_cmd1(argv[1], argv[2], envp, fildes);
		}
		wait(NULL);
		execute_cmd2(argv[4], argv[3], envp, fildes);
	}
	return (0);
}
