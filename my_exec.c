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

char *my_check_path(char const *arg, char **path)
{
    char *buff = my_strcpy(arg);
    int check;
    int i = 0;

    for (; (check = access(buff, X_OK)) == -1 && path[i] != NULL; i++) {
        free(buff);
        buff = my_strcat(path[i], "/");
        buff = my_strcat(buff, arg);
    }
    for (i = 0; buff[i] != '\0'; i++) {
        if (buff[i] == '/')
            break;
    }
    if ((check == -1) || (buff[i] == '\0')) {
        free(buff);
        my_putstr(arg);
        my_putstr(": Command not found.\n");
        return (NULL);
    }
    return (buff);
}

int my_exec(char **prog_av, char **env, int p[2])
{
    int Child_status = 0;
    int Child_PID;
    char **path = my_getpath_in_env(env);
    char *buff = my_check_path(prog_av[0], path);

    if (buff == NULL)
        return (1);
    Child_PID = fork();
    if (Child_PID == 0) {
        execve(buff, prog_av, env);
        free(buff);
        free_tab(path);
        reset_fd(p);
    }
    else
        waitpid(Child_PID, &Child_status, 0);
    if (Child_status)
        check_err(Child_status);
    return (0);
}