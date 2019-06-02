/*
** EPITECH PROJECT, 2018
** my_str_functions
** File description:
** str_ or tab_ functions 2
*/
#include "my.h"

void free_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
}

int my_str_is_empty(char const *str)
{
    if ((str == NULL) || (*str == 0))
        return (1);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != ';')
            return (0);
    }
    return (1);
}

char **my_tabcat_replace(char **src, char *str)
{
    char **dest = my_tabcat(src, str);

    if (src != NULL)
        free_tab(src);
    return (dest);
}