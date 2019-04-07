/*
** EPITECH PROJECT, 2018
** my_exec2
** File description:
** execution with redirections
*/
#include "my.h"

char ***my_get_exec_av(char const **prog_av)
{
    char ***exec_av;
    int j = 0;
    int s = 0;

    for (; prog_av[j] != NULL; j = j + 1) {
        if (prog_av[j][0] == '|')
            s = s + 1;
    }
    exec_av = malloc(sizeof(char**) * (s + 2));
    for (int i = 0, j = 0; prog_av[i] != NULL; i = i + 1) {
        if (prog_av[i][0] == '|')
            j = j + 1;
        else if ((prog_av[i][0] == '>') || (prog_av[i][0] == '<'))
            i = i + 1;
        else
            exec_av[j] = my_tabcat(exec_av[j], prog_av[i]);
    }
    exec_av[s + 1] = NULL;
    return (exec_av);
}

int my_check_cmd(char **prog_av)
{
    int in = 0;
    int out = 0;
    int p = 0;
    int err = 0;

    for (int j = 0; prog_av[j] != NULL; j = j + 1) {
        if (prog_av[j][0] == '>') {
            out = out + 1;
        }
        else if (prog_av[j][0] == '<') {
            err = p;
            in = in + 1;
        }
        if (((in > 1) || (out > 1)) || (err > 0))
            my_str_err(prog_av[j][0]);
        else if (check_pipe(prog_av, j, out)) {
            p = p + 1;
        }
    }
    return (0);
}

int my_exec2(char **prog_av, char **env)
{
    char ***exec_av = my_get_exec_av(prog_av);
    int ac;
    int a = 0;
    int s = 0;
    int i = 0;
    int pipefd[2];

    for (; exec_av[i + 1] != NULL; i = i + 1) {
        for (ac = 0; exec_av[i][ac] != NULL; ac = ac + 1);
        // for (s = s + ac; a < s; a = a + 1) {
        //     if ((prog_av[a][0] == '>') || (prog_av[a][0] == '<'))
        //         my_redirections(prog_av[a], prog_av[a + 1]);
        // }
        my_pipe(exec_av[i], env);
    }
    my_chose_function(exec_av[i], env, 1);
    return (0);
}

int my_exec_for(char *cmdline, char **env)
{
    char *cmd;
    char **prog_av;
    int fd[2];
    int i0 = 0;

    for (int i = 0; cmdline[i] != '\0'; i = i + 1) {
        if (cmdline[i] == ';') {
            cmd = my_strncpy(&cmdline[i0], (i - i0));
            prog_av = my_str_to_cmd_arr(cmd);
            free(cmd);
            i0 = i + 1;
            if (my_check_cmd(prog_av));
                continue;
            my_exec2(prog_av, env);
            free(prog_av);
        }
    }
    return (0);
}