/*
** EPITECH PROJECT, 2018
** my_put_functions
** File description:
** put_ functions
*/
#include "my.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

int    my_putstr(char const *str)
{
    int a = 0;

    while (str[a] != '\0') {
        my_putchar(str[a]);
        a = a + 1;
    }
    return (0);
}

int my_puttab(char **tab)
{
    int a = 0;

    while (tab[a] != NULL) {
        my_putstr(tab[a]);
        my_putchar('\n');
        a = a + 1;
    }
    return (0);
}

int my_put_nbr(int nb)
{
    if (nb < 0)
    {
        my_putchar('-');
        nb = nb * (-1);
    }
    if (nb > 9)
        my_put_nbr(nb / 10);
    nb = (nb % 10);
    if (nb >= 0 && nb <= 9)
    {
        my_putchar(nb + '0');
    }
    return (nb);
}

char *my_give_target(int argc, char **argv, char **env, char const *last)
{
    char *target = NULL;
    DIR *check;

    if (argc == 1)
        target = my_strcpy(&my_get_in_env("HOME=", env)[5]);
    else if ((argv[1][0] == '-') && (argv[1][1] == '\0')) {
        if (last != NULL)
            target = my_strcpy(last);
    }
    else {
        if ((check = opendir(argv[1]))) {
            closedir(check);
            target = my_strcpy(argv[1]);
        }
    }
    return (target);
}