/*
** EPITECH PROJECT, 2018
** my_errors
** File description:
** errors messages
*/
#include "my.h"

void my_str_err(int errno)
{
    if (errno == -1)
        my_putstr("Missing name for redirect.\n");
    if (errno == 0)
        my_putstr("Invalid null command.\n");
    if (errno == 1)
        my_putstr("Ambiguous input redirect.\n");
    if (errno == 2)
        my_putstr("Ambiguous output redirect.\n");
}