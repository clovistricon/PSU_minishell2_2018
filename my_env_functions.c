/*
** EPITECH PROJECT, 2018
** my_env_functions
** File description:
** functions related to environment
*/

#include "my.h"

char *my_get_in_env(char const *key, char **env)
{
    int i;
    int j;

    for (i = 0; env[i] != NULL; i = i + 1) {
        for (j = 0; key[j] != '\0' && env[i][j] == key[j]; j++);
        if (key[j] == '\0')
            return (env[i]);
    }
    return (NULL);
}

char **my_str_to_pathlist(char const *paths)
{
    int len = 0;
    int i;
    int s = 0;
    int b;
    char **pathlist;

    for (i = 0; paths[i] != '\0'; i = i + 1)
        len = (paths[i] == ':') ? (len + 1) : (len);
    pathlist = malloc(sizeof(char*) * (len + 2));
    for (int a = 0; a < (len + 1); a = a + 1) {
        for (i = s; paths[i] != ':' && paths[i] != '\0'; i = i + 1);
        pathlist[a] = malloc(sizeof(char) * ((i - s) + 1));
        for (b = 0; paths[s] != ':' && paths[s] != '\0'; b = b + 1)
            pathlist[a][b] = paths[s++];
        pathlist[a][b] = '\0';
        s = s + 1;
    }
    pathlist[len + 1] = NULL;
    return (pathlist);
}

char **my_getpath_in_env(char **env)
{
    char **pathlist;
    char *buff = my_get_in_env("PATH=", env);

    if (buff == NULL)
        return (NULL);
    else
        pathlist = my_str_to_pathlist(&buff[5]);
    return (pathlist);
}

char **my_unsetenv(int argc, char **argv, char **env)
{
    int j;
    char **tmp = NULL;

    if (argc < 2) {
        my_putstr("unsetenv: Too few arguments.\n");
        return (env);
    }
    for (int i = 0; env[i] != NULL; i = i + 1) {
        for (j = 0; argv[1][j] != '\0' && env[i][j] == argv[1][j]; j++);
        if ((argv[1][j] == '\0') && (env[i][j] == '='))
            continue;
        else
            tmp = my_tabcat_replace(tmp, env[i]);
    }
    free_tab(env);
    return (tmp);
}

char **my_setenv(int argc, char **argv, char **env)
{
    int j;
    char *elem;

    if (my_setenv_err(argc, argv, env) > 0)
        return (env);
    elem = my_strcat(argv[1], "=");
    if (argc == 3)
        elem = my_strcat(elem, argv[2]);
    for (int i = 0; env[i] != NULL; i = i + 1) {
        for (j = 0; argv[1][j] != '\0' && env[i][j] == argv[1][j]; j++);
        if ((argv[1][j] == '\0') && (env[i][j] == '=')) {
            free(env[i]);
            env[i] = elem;
            return (env);
        }
    }
    env = my_tabcat_replace(env, elem);
    free(elem);
    return (env);
}