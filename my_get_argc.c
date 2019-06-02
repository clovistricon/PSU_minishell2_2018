/*
** EPITECH PROJECT, 2018
** my_get_argc
** File description:
** get ac and redirections
*/
#include "my.h"

void reset_fd(int p[2])
{
    dup2(p[0], 0);
    dup2(p[1], 1);
}

int my_get_argc(char **av)
{
    int ac;
    int argc = 0;
    int check = 0;

    for (ac = 0; av[ac] != NULL; ac = ac + 1);
    for (int s = 0; s < (ac - 1); s++) {
        if ((av[s][0] == '>') || (av[s][0] == '<')) {
            argc = ((argc == 0) ? (s) : (argc));
            check = my_redirections(av[s], av[s + 1]);
        }
        if (check == 84)
            my_str_err(1);
    }
    if (argc == 0)
        return (ac);
    return (argc);
}