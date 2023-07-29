#include <unistd.h> // pipe(), fork(), execve(), dup2(), close()
#include <fcntl.h> // open()
#include <stdlib.h> // exit
#include <stdio.h> // perror
#include <sys/wait.h> // waitpid()

void child_process(char **cmd, int input_fd, int *fds, char **envp)
{
	if (input_fd[0] != -1)
	{
		dup2(input_fd[0], STDIN_FILENO);
		close(input_fd[0]); // No loged needed, cause the 
		close(input_fd[1]);
	}
}

void parent_process(char **cmd, int *input_fd, char **envp)
{
	if (input_fd[0] != -1)
	{
		dup2(input_fd[0], STDIN_FILENO);
		close(input_fd[0];
		close(input_fd[1]);
	}
	int out_fd = 
}

int main(int argc, char **argv, char *envp)
{
	int fds[2];
	int	input_fd[2]
	char	**cmd;
	int		i;

	if(argc < 5)
	{
		if (argc < 5)
		{
			ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 ... outfile\n", 2);
			return (1);
		}
		input_fd[0] = -1;
		input_fd[1] = -1;
		i = 2;
		while(i < argc -2)
		{
			pipe(fds);
			if (!(ford())
			{
				child_process(argv[i], input_fd, fds, envp);
			}
			close(input_fd[0]);
			close(input_fd[1]);
			input_fd[0] = fds[0];
			input_fd[1] = fds[1];
		}
	
	parent_process(argv[argc - 2], input_fd, envp);

	return (0);
	}
}

void	here_doc(char *limiter, int argc)
{
	pid_t	here_doc_reader_process;
	int		fd[2];
	char	*line;

	if (argc < 6)
		usage();
	if (pipe(fd) == -1)
		error();
	here_doc_reader_process = fork();
	if (here_doc_reader_process == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			// if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			if(ft_strcmp(line, limiter) == 0)
			{
				// the original code didn't free line, but I think it should
				free(line);
				exit(EXIT_SUCCESS);

			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1); // Not sure if get_next_line removes the \n
			free(line);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}
