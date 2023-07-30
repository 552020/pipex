#include "pipex.h"

void exit_with_error(const char *msg, bool is_system_error)
{
	if (is_system_error)
		perror(msg);
	else
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd((char *)msg, 2);
	}
	exit(1);
}

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
	handle_quotes_with_space_between(&cmd);
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
	handle_quotes_with_space_between(&cmd);
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

void remove_element_at_index(char ***arr, int index)
{
    int i = 0;
    char **new_arr;

    while ((*arr)[i])
        i++;
    new_arr = (char **)malloc(sizeof(char *) * i);
    if (!new_arr)
        return;
    for (i = 0; i < index; i++)
        new_arr[i] = (*arr)[i];
    for (; (*arr)[i]; i++)
        new_arr[i] = (*arr)[i + 1];
    free(*arr);
    *arr = new_arr;
}


void    handle_quotes_with_space_between(char ***arr)
{
    int i = 0;
    int j;
    char *temp;
    char *space = " ";

    while ((*arr)[i])
    {
        if ((*arr)[i][0] == '\'')
        {
            j = i;
            while ((*arr)[j] && (*arr)[j][ft_strlen((*arr)[j]) - 1] != '\'')
                j++;
            while (i < j)
            {
                char *temp_with_space = ft_strjoin((*arr)[i], space);
                temp = ft_strjoin(temp_with_space, (*arr)[i + 1]);
                free(temp_with_space);
                free((*arr)[i]);
                (*arr)[i] = temp;
                remove_element_at_index(arr, i + 1);  // You need to implement this function
                j--;
            }
            temp = ft_substr((*arr)[i], 1, ft_strlen((*arr)[i]) - 2);
            free((*arr)[i]);
            (*arr)[i] = temp;
        }
        i++;
    }
}



