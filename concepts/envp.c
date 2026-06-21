#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	int i = 0;

	printf("argc: %d\n", argc);
	while(argv[i])
	{
		printf("argv: %s\n", argv[i]);
		i++;
	}
	i = 0;
	while(envp[i])
	{
		printf("envp: %s\n", envp[i]);
		i++;
	}
	return (0);
}
