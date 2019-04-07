/*
** EPITECH PROJECT, 2018
** my_pipe
** File description:
** redirections
*/
#include "my.h"


char *my_get_cmd_pipe(char *str)
{
    char *cmd;
    int s = 0;
    int i1 = 0;
    int i = 0;

    for (; str[i] != '\0'; i++, s++)
        s = ((str[i] == '|') ? (s + 2) : (s));
    cmd = malloc(sizeof(char) * (s + 1));
    for (int i2 = 0; i1 < s; i1++, i2++) {
        if (i2 >= i)
            cmd[i1] = ' ';
        else if (str[i2] == '|') {
            cmd = my_strcat(cmd, " | ");
            i1 = i1 + 2;
        }
        else
            cmd[i1] = str[i2];
    }
    cmd[i1] = '\0';
    free(str);
    return (cmd);
}

char *my_get_cmd(char const *str, int s1, int s2)
{
    char *cmd = malloc(sizeof(char) * (s2 + 1));
    int i1 = 0;
    int i2 = 0;

    for (; i1 < s2; i1++, i2++) {
        if (i2 >= s1)
            cmd[i1] = ' ';
        else if ((str[i2] == '>') || (str[i2] == '<')) {
            cmd[i1++] = ' ';
            cmd[i1] = str[i2++];
            ((cmd[i1++] == str[i2]) ? (cmd[i1] = str[i2]) : (cmd[i1] = ' '));
        }
        else
            cmd[i1] = str[i2];
    }
    cmd[s2] = '\0';
    return (cmd);
}

char **my_str_to_cmd_arr(char *str)
{
    char *cmd;
    char **tab;
    int i = 0;
    int s = 0;

    if ((str == NULL) || (*str == 0))
        return (NULL);
    for (; str[i] != '\0'; i++) {
        if ((str[i] == '>') || (str[i] == '<')) {
            i = ((str[i] == str[i + 1]) ? (i + 1) : (i));
            s = s + 2;
        }
    }
    cmd = my_get_cmd(str, i, i + s);
    cmd = my_get_cmd_pipe(cmd);
    tab = my_str_to_word_array(cmd);
    free(cmd);
    return (tab);
}

int my_put_out(char const *direc, char const *file)
{
    int fd;

    if ((direc[0] == '>') && (direc[1] == '>')) {
        if ((fd = open(file, O_CREAT | O_WRONLY | O_APPEND)) > 0)
            dup2(fd, 1);
    }
    else if (direc[0] == '>') {
        if ((fd = open(file, O_CREAT | O_WRONLY | O_TRUNC)) == -1)
            return (-1);
        dup2(fd, 1);
    }
    return (0);
}

int my_put_in(char const *direc, char const *file)
{
    int fd;

    if ((direc[0] == '<') && (direc[1] == '<'))
        get_keyboard(file);
    else if (direc[0] == '<') {
        if ((fd = open(file, O_WRONLY)) == -1)
            return (-1);
        dup2(fd, 0);
    }
    return (0);
}