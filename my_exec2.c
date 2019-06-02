/*
** EPITECH PROJECT, 2018
** my_exec2
** File description:
** execution with redirections
*/
#include "my.h"

char ***my_get_exec_av(char **prog_av)
{
    char ***exec_av;
    int j = 0;
    int s = 0;

    for (; prog_av[j] != NULL; j = j + 1)
        s = ((prog_av[j][0] == '|') ? (s + 1) : (s));
    exec_av = malloc(sizeof(char**) * (s + 2));
    for (int j0 = 0; j0 < (s + 2); j0++)
        exec_av[j0] = NULL;
    for (int i = 0, j = 0; prog_av[i] != NULL; i = i + 1) {
        if (prog_av[i][0] == '|')
            j = j + 1;
        else if ((prog_av[i][0] == '>') || (prog_av[i][0] == '<'))
            i = i + 1;
        else
            exec_av[j] = my_tabcat(exec_av[j], prog_av[i]);
    }
    return (exec_av);
}

int my_check_cmd(char **prog_av)
{
    int in = 0;
    int out = 0;
    int p = 0;
    int err = 0;

    for (int j = 0; (prog_av[j] != NULL) && (err == 0); j = j + 1) {
        if (prog_av[j][0] == '>')
            err = check_pipe(prog_av, j, ++out, 0);
        if (prog_av[j][0] == '<') {
            err = check_pipe(prog_av, j, ++in, 1);
            err = ((p > 0) ? (my_str_err(3)) : (err));
        }
        if (prog_av[j][0] == '|') {
            err = check_pipe(prog_av, j, 0, 0);
            err = ((out > 0) ? (my_str_err(4)) : (err));
            p++;
        }
    }
    return (err);
}

int my_exec2(char **prog_av, char ***env)
{
    char ***exec_av = my_get_exec_av(prog_av);
    int i = 0;
    int init_pipe[2];

    init_pipe[0] = dup(0);
    init_pipe[1] = dup(1);
    for (; exec_av[i + 1] != NULL; i = i + 1)
        my_pipe(exec_av[i], env, init_pipe);
    (*env) = my_chose_function(exec_av[i], *env, init_pipe);
    dup2(init_pipe[0], 0);
    dup2(init_pipe[1], 1);
    return (0);
}

int my_exec_pipe(char *cmd, char ***env)
{
    char **prog_av;

    prog_av = my_str_to_cmd_arr(cmd);
    if (my_check_cmd(prog_av) != 0)
        return (-1);
    my_exec2(prog_av, env);
    free_tab(prog_av);
    return (0);
}

int my_exec_for(char const *cmdline, char ***env)
{
    char *cmd = my_strcpy(cmdline);
    char *tmp;

    for (int i = 0; cmd[i] != '\0'; i = i + 1) {
        if (cmd[i] == ';') {
            tmp = my_strncpy(cmd, i);
            (my_str_is_empty(tmp) == 0) ? my_exec_pipe(tmp, env) : 0;
            free(tmp);
            cmd = my_str_replace(cmd, &cmd[i + 1]);
            i = -1;
        }
        if ((cmd == NULL) || (*cmd == 0))
            return (0);
    }
    my_exec_pipe(cmd, env);
    free(cmd);
    return (0);
}