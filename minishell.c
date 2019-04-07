/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** entry of command
*/
#include "my.h"

void my_cd(int argc, char **argv, char **env)
{
    static char *last = NULL;
    char *buff = malloc(sizeof(char) * 300);
    char *target = NULL;

    if (argc > 2) {
        my_putstr("cd: Too many arguments.\n");
        return;
    }
    target = my_give_target(argc, argv, env, last);
    if (target == NULL) {
        if ((argv[1][0] != '-') || (argv[1][1] != '\0'))
            my_putstr(argv[1]);
        if (access(argv[1], F_OK) == -1)
            my_putstr(": No such file or directory.\n");
        else
            my_putstr(": Not a directory.\n");
    } else {
        last = getcwd(buff, 256);
        chdir(target);
    }
}

int my_is_keystr(char const *str)
{
    char *keys[5] = { "cd", "exit", "setenv", "unsetenv", "env" };

    for (int i = 0; str[i] != '\0'; i = i + 1) {
        if (my_strcomp(keys[i], str) == 0)
            return (i);
    }
    return (-1);
}

char **my_chose_function(char **argv, char **env, int p)
{
    int argc;

    for (argc = 0; argv[argc]; argc = argc + 1);
    if (argc == 0)
        return (env);
    switch(my_is_keystr(argv[0])) {
        case 0: my_cd(argc, argv, env);
            break;
        case 1: my_putstr("exit\n");
            exit(0);
            break;
        case 2: env = my_setenv(argc, argv, env);
            break;
        case 3: env = my_unsetenv(argc, argv, env);
            break;
        case 4: my_puttab(env);
            break;
        default: my_exec(argv, env, p);
    }
    return (env);
}

int waiting_input(char **env)
{
    char *line;
    char path[300];
    int end = 0;

    while (end == 0) {
        getcwd(path, 256);
        my_putstr(path);
        my_putstr("$>");
        line = get_next_line(0);
        if (line == NULL) {
            my_putchar('\n');
            exit(0);
        }
        else if (line[0] == 0)
            continue;
        my_exec_for(line, env);
        free(line);
    }
    return (0);
}

int main(int ac, char **av, char **env)
{
    int check = 0;
    char **tab;

    if (ac == 1) {
        tab = my_tabcpy(env);
        check = waiting_input(tab);
        free(tab);
        if (check == -1)
            return (0);
    }
    else
        return (84);
    return (0);
}