/*
** EPITECH PROJECT, 2018
** my_pipe
** File description:
** redirections
*/
#include "my.h"

int check_pipe(char **av, int j, int out)
{
    // if (av[j][0] == '>') {
    //     if ((*av[j + 1] == '>') || (*av[j + 1] == '<') || (*av[j + 1] == '|'))
    //     else if (j == 0)
    // }
    // else if ((av[j][0] == '|') && ((av[j + 1] == NULL) || (*av[j + 1] == '|')))
    //     my_str_err(0);
    // else {
    // }
    return (0);
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

// int *my_redirections(char const **prog_av)
// {
//     int fd;
//     int fdout = 1;
//     int fdin = 0;

//     if ((fd = my_put_out(prog_av[i], prog_av[i + 1], fdout)) == -1)
//         return (84);
//     else if ((fd = my_put_in(prog_av[i], prog_av[i + 1], fdin)) == -1)
//         return (84);
//     return (0);
// }

int my_pipe(char **prog_av, char **env)
{
    int pid;
    int status;
    int pipefd[2];

    pipe(pipefd);
    pid = fork();
    if (pid == 0) {
        close(pipefd[0]);
        my_chose_function(prog_av, env);
    }
    else {
        close(pipefd[1]);
    }
    return (0);
}