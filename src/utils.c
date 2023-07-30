#include "pipex.h"

char *extract_path_env(char **envp)
{
	int i = 0;
	char *path_env;

	path_env = NULL;
	while (envp[i])
	{
		if(ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i];
			break ;
		}
		i++;
	}
	if (!path_env)
	{
		ft_putstr_fd("PATH environment variable not found\n", 2);
		exit(1);
	}
	path_env = path_env + 5;
	return (path_env);
}

char *extract_path(char *path_env, char *cmd)
{
	char **path_dirs;
	char *full_path;
	char *tmp_path;
	int i;

	i = 0;


	path_dirs = ft_split(path_env, ':');
	while(path_dirs[i])
	{
		tmp_path = ft_strjoin(path_dirs[i], "/");
		full_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if(access(full_path, F_OK) == 0)
		{
			i = -1;
			while(path_dirs[++i])
				free(path_dirs[i]);
			free(path_dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	i = -1;
	while(path_dirs[++i])
		free(path_dirs[i]);
	free(path_dirs);
	return (NULL);
}

int execute_cmd1(char *infile, char *cmd1, char **envp, int *fildes)
{
	char 	**cmd;
	char	*path_env;
	char	*path;
	int 	infile_fildes;

	close(fildes[0]);
	infile_fildes = open(infile, O_RDONLY);
	if (infile_fildes < 0)
	{
		ft_putstr_fd("Error opening input file\n", 2);
		exit(1);
	}
	dup2(infile_fildes, STDIN_FILENO);
	close(infile_fildes);
	dup2(fildes[1], STDOUT_FILENO);
	close(fildes[1]);
	cmd = ft_split(cmd1, ' ');
	path_env = extract_path_env(envp);
	path = extract_path(path_env, cmd[0]);
	if (!path)
	{
		ft_putstr_fd("Command not found\n", 2);
		return (1);
	}
	execve(path, cmd, envp);
	return (0);
}

int execute_cmd2(char *outfile, char *cmd2, char **envp, int *fildes)
{
	char 	**cmd;
	char	*path_env;
	char	*path;
	int 	outfile_fildes;

	close(fildes[1]);
	outfile_fildes = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fildes < 0)
	{
		ft_putstr_fd("Error opening output file\n", 2);
		exit(1);
	}
	dup2(outfile_fildes, STDOUT_FILENO);
	close(outfile_fildes);
	dup2(fildes[0], STDIN_FILENO);
	close(fildes[0]);
	cmd = ft_split(cmd2, ' ');
	path_env = extract_path_env(envp);
	path = extract_path(path_env, cmd[0]);
	if (!path)
	{
		ft_putstr_fd("Command not found\n", 2);
		return (1);
	}
	execve(path, cmd, envp);
	return (0);
}

