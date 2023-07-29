#include <stdlib.h>
#include <unistd.h>

#define PATH_PREFIX "PATH="

char *find_env_var(char **envp, const char *var)
{
    int i = 0;
    int var_length = strlen(var);

    while (envp[i])
    {
        if (strncmp(envp[i], var, var_length) == 0)
            return (envp[i] + var_length);
        i++;
    }
    return (NULL);
}

char *find_path(char *cmd, char **envp)
{
    char **paths;
    char *path;
    int  i;
    char *part_path;
    char *path_env_var = find_env_var(envp, PATH_PREFIX);

    if (path_env_var == NULL)
        return NULL; // or return "command not found";

    paths = ft_split(path_env_var, ':');
    i = 0;
    while (paths && paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, cmd);
        free(part_path);
        if (access(path, F_OK) == 0)
        {
            while (paths[++i])
                free(paths[i]);
            free(paths);
            return path;
        }
        free(path);
        i++;
    }
    i = -1;
    while (paths && paths[++i])
        free(paths[i]);
    free(paths);
    return NULL; // or return "command not found";
}
