#include <stdio.h>
#include <string.h>

char	**ft_split(const char *s, char c);

int main(int argc, char **argv, char **envp)
{
	int i = 0;
	const char *cmd;
	char	*path_env;
	char	**path_dirs;

	if (argc < 2) {
			fprintf(stderr, "Please provide a command to execute.\n");
			return 1;
	}
	cmd = argv[1];
	path_env = NULL;

	while (envp[i])
	{
		if(strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i];
			break ;
		}
		i++;
	}
	if (!path_env)
	{
		fprintf(stderr, "PATH environment variable not found\n");
	}
	printf("path_env: %s\n", path_env);
	path_env = path_env + 5;
	path_dirs = ft_split(path_env, ':');
	i = 0;
	while (path_dirs[i])
	{
		printf("path_dird[%d]: %s\n", i, path_dirs[i]);
		i++;
	}
	

	return (0);
}


