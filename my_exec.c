/*
** EPITECH PROJECT, 2018
** my_exec
** File description:
** execute file
*/
#include "my.h"

int my_str_isalphanum(char const *str)
{
    if ((str[0] < 65) || (str[0] > 122))
        return (1);
    else if ((str[0] > 90) && (str[0] < 97))
        return (1);
    for (int i = 0; str[i] != '\0'; i = i + 1) {
        if ((str[i] < 48) || (str[i] > 122))
            return (2);
        else if ((str[i] > 57) && (str[i] < 65))
            return (2);
        if ((str[i] > 90) && (str[i] < 97))
            return (2);
    }
    return (0);
}

int my_setenv_err(int argc, char **argv, char **env)
{
    if (argc == 1) {
        my_puttab(env);
        return (1);
    }
    else if (argc > 3) {
        my_putstr("setenv: Too many arguments.\n");
        return (2);
    }
    if (my_str_isalphanum(argv[1]) == 1) {
        my_putstr("setenv: Variable name must begin with a letter.\n");
        return (3);
    }
    else if (my_str_isalphanum(argv[1]) == 2) {
        my_putstr("setenv");
        my_putstr(": Variable name must contain alphanumeric characters.\n");
        return (4);
    }
    return (0);
}

int check_err(int Child_status)
{
    char *msg;

    if (WIFSIGNALED(Child_status)) {
        if (WCOREDUMP(Child_status))
            write(2, "Segmentation fault\n", 20);
        else {
            msg = strsignal(WTERMSIG(Child_status));
            write(2, msg, 256);
        }
        return (84);
    }
    return (0);
}

int my_check_path(char const *buff, char const *arg)
{
    if (access(buff, F_OK) == -1) {
        my_putstr(arg);
        my_putstr(": Command not found.\n");
        return (-1);
    }
    return (0);
}

int my_exec(char **prog_av, int len, char **env, int p)
{
    int Child_status = 0;
    int Child_PID;
    char **path = my_getpath_in_env(env);
    char *buff = my_strcpy(prog_av[0]);

    for (int a = 0; access(buff, F_OK) == -1 && path[a] != NULL; a = a + 1) {
        buff = my_strcpy(path[a]);
        buff = my_strcat(buff, "/");
        buff = my_strcat(buff, prog_av[0]);
    }
    if (my_check_path(buff, prog_av[0]) == -1)
        return (1);
    prog_av[0] = my_strcpy(buff);
    Child_PID = ((p == 1) ? (fork()) : (0));
    if (Child_PID == 0)
        execve(prog_av[0], prog_av, env);
    // if (p == 1)
    //     waitpid(Child_PID, &Child_status, 0);
    if (Child_status)
        check_err(Child_status);
    return (0);
}