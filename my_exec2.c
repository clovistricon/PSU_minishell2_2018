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

int my_exec2(char **prog_av, char **env)
{
    char ***exec_av = my_get_exec_av(prog_av);
    int ac;
    int a = 0;
    int s = 0;
    int i = 0;

    for (; exec_av[i + 1] != NULL; i = i + 1) {
        for (ac = 0; exec_av[i][ac] != NULL; ac = ac + 1);
        for (s = s + ac; a < s; a = a + 1) {
            if ((prog_av[a][0] == '>') || (prog_av[a][0] == '<'))
                my_redirections(prog_av[a], prog_av[a + 1]);
        }
        my_pipe(exec_av[i], env);
    }
    my_chose_function(exec_av[i], env, 1);
    return (0);
}

int my_exec_pipe(char *cmdline, char **env, int i0, int i)
{
    char *cmd;
    char **prog_av;

    cmd = my_strncpy(&cmdline[i0], (i - i0));
    prog_av = my_str_to_cmd_arr(cmd);
    free(cmd);
    if (my_check_cmd(prog_av) != 0)
        return (-1);
    my_exec2(prog_av, env);
    free(prog_av);
    return (0);
}

int my_exec_for(char *cmdline, char **env)
{
    int i0 = 0;
    int i = 0;
    int check = 0;

    for (; cmdline[i] != '\0'; i = i + 1) {
        if (cmdline[i] == ';') {
            check = my_exec_pipe(cmdline, env, i0, i);
            i0 = i + 1;
        }
        if (check == -1)
            return (check);
    }
    my_exec_pipe(cmdline, env, i0, i);
    return (0);
}