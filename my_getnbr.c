/*
** EPITECH PROJECT, 2018
** my_getnbr
** File description:
** task05
*/
#include "my.h"

int my_pow(int p)
{
    int a = 1;
    int result = 10;

    if (p == 0)
        return (1);
    for (; a < p; a = a + 1) {
        result = result * 10;
    }
    return (result);
}

int my_getnbr(char const *str)
{
    int nb = 0;
    int a = 0;
    int b;
    int s;

    for (; (str[a] < 48) || (str[a] > 57); a = a + 1);
    b = a;
    s = a;
    for (; (str[b] > 47) && (str[b] < 58); b = b + 1);
    b = b - 1;
    for (; a <= b; a = a + 1) {
        if (((nb + (str[a] - '0')) * my_pow(b - a)) <= 2147483647)
            nb = nb + ((str[a] - '0') * my_pow(b - a));
    }
    if ((s > 0) && (str[s - 1] == '-'))
        nb = nb * (-1);
    return (nb);
}