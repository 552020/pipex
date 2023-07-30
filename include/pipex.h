#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "libft.h"

int execute_cmd1(char *infile, char *cmd1, char **envp, int *fildes);
int execute_cmd2(char *outfile, char *cmd2, char **envp, int *fildes);
void    handle_quotes_with_space_between(char ***arr);
void exit_with_error(const char *msg, bool is_system_error);