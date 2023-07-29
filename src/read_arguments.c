#include <stdio.h>
#include <stdlib.h>

char	**ft_split(const char *s, char c);
void    handle_quotes(char ***arr);
void    handle_quotes_with_space_between(char ***arr);

int	main(int argc, char **argv)
{
	int		i;
	char	**cmds;

	i = 0;
	while (i < argc)
	{
		printf("argv[%d]: %s\n", i, argv[i]);
		i++;
	}
	printf("\n");
	i = 0;

	cmds = malloc(sizeof(char *) * argc);
	if (!cmds)
		return (1);

	i = 1;
	while (i < argc)
	{
		// Print the results after split
		printf("After ft_split:\n");
		printf("argv[%d]: %s\n", i, argv[i]);
		cmds = ft_split(argv[i], ' ');
		for (int j = 0; cmds[j]; j++)
		{
			printf("argv[%d][%d]: %s\n",i, j, cmds[j]);
			// free(cmds[j]);
		}

		handle_quotes_with_space_between(&cmds); // call handle_quotes to handle single quotes

		// Print the results after handle_quotes
		printf("After handle_quotes:\n");
		for (int j = 0; cmds[j]; j++)
		{
			printf("argv[%d][%d]: %s\n",i, j, cmds[j]);
		}
		// Free memory
		for (int j = 0; cmds[j]; j++)
		{
			free(cmds[j]);
		}
		free(cmds);
		i++;
	}
	return (0);
}
