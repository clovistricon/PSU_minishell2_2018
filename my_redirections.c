/*
** EPITECH PROJECT, 2018
** my_pipe
** File description:
** redirections
*/
#include "my.h"

int check_pipe(char **av, int j, int entry, int in)
{
    int check = 0;

    if (j == 0) {
        my_str_err(2);
        return (1);
    }
    if ((av[j][0] == '>') || (av[j][0] == '<')) {
        if (av[j + 1] == NULL) {
            my_str_err(2);
            return (1);
        }
        if ((*av[j + 1] == '>') || (*av[j + 1] == '<') || (*av[j + 1] == '|'))
            check = my_str_err(1);
    }
    else if ((av[j][0] == '|') && ((av[j + 1] == NULL) || (*av[j + 1] == '|')))
        check = my_str_err(2);
    if (entry > 1)
        check = ((in == 1) ? (my_str_err(3)) : (my_str_err(4)));
    return (check);
}

int get_keyboard(char const *str)
{
    char *line = NULL;

    while (my_strcomp(line, str) == 0) {
        my_putchar('>');
        line = get_next_line(0);
    }
    return (0);
}

int my_redirections(char const *direction, char const *arg)
{
    if (my_put_out(direction, arg) == -1)
        return (84);
    else if (my_put_in(direction, arg) == -1)
        return (84);
    return (0);
}

int my_pipe(char **prog_av, char **env, int p[2])
{
    int pid;
    int status;
    int pipefd[2];

    pipe(pipefd);
    pid = fork();
    if (pid == 0) {
        dup2(pipefd[1], 1);
        close(pipefd[0]);
        close(pipefd[1]);
        my_chose_function(prog_av, env, p);
        exit(0);
    }
    else {
        dup2(pipefd[0], 0);
        close(pipefd[1]);
        close(pipefd[0]);
    }
    return (0);
}