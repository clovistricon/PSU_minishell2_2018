/*
** EPITECH PROJECT, 2018
** my_errors
** File description:
** errors messages
*/
#include "my.h"

int my_str_err(int err)
{
    if (err == 1)
        my_putstr("Missing name for redirect.\n");
    if (err == 2)
        my_putstr("Invalid null command.\n");
    if (err == 3)
        my_putstr("Ambiguous input redirect.\n");
    if (err == 4)
        my_putstr("Ambiguous output redirect.\n");
    return (1);
}