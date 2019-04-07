/*
** EPITECH PROJECT, 2018
** my_str_functions
** File description:
** str_ or tab_ functions
*/
#include "my.h"

char *my_strncpy(char const *src, int len)
{
    char *str;
    int s = 0;

    if ((src == NULL) || (*src == 0) || (len <= 0))
        return (NULL);
    for (; (src[s] != '\0') && (s < len); s = s + 1);
    str = malloc(sizeof(char) * (s + 1));
    for (int i = 0; i < s; i = i + 1)
        str[i] = src[i];
    str[s] = '\0';
    return (str);
}

int my_strcomp(char const *str1, char const *str2)
{
    if ((str1 == NULL) && (str2 == NULL))
        return (0);
    else if ((str1 == NULL) || (str2 == NULL))
        return (-1);
    for (int i = 0; str1[i] != '\0'; i = i + 1) {
        if (str1[i] != str2[i])
            return (-1);
    }
    return (0);
}

char **my_tabcpy(char **src)
{
    int a = 0;
    int len;
    char **dest;

    for (len = 0; src[len] != NULL; len = len + 1);
    dest = malloc(sizeof(char*) * (len + 1));
    while (src[a] != NULL) {
        dest[a] = my_strcpy(src[a]);
        a = a + 1;
    }
    dest[a] = NULL;
    return (dest);
}

char **my_tabcat(char **src, char const *str)
{
    int a = 0;
    int len = 0;
    char **dest;

    if ((str == NULL) || (*str == 0))
        return (src);
    if (src)
        for (; src[len] != NULL; len = len + 1);
    dest = malloc(sizeof(char*) * (len + 2));
    if (src) {
        while ((src[a] != NULL) && (*src[a] != '\0')) {
            dest[a] = my_strcpy(src[a]);
            a = a + 1;
        }
    }
    dest[a++] = my_strcpy(str);
    dest[a] = NULL;
    return (dest);
}

char **my_tabtrunc(char **src, int end)
{
    char **tab = malloc(sizeof(char*) * (end + 1));
    int i = 0;

    while ((i < end) && (src[i]))
        tab[i] = my_strcpy(src[i++]);
    tab[i][0] = '\0';
}