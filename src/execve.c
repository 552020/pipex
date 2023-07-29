#include <stdio.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{
	int i = 0;
	const char *cmd;
	char*	path_env;

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
	return (0);
}


