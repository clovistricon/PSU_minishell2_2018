/*
** EPITECH PROJECT, 2018
** my
** File description:
** functions for minishell
*/
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

#ifndef MY_H_
#define MY_H_
int my_pow(int p);
int my_getnbr(char const *str);
void my_putchar(char c);
int my_putstr(char const *str);
int my_puttab(char **tab);
int my_put_nbr(int nb);
char **my_str_to_params(char const *str);
char **my_str_to_word_array(char const *str);
char **my_str_to_cmd_arr(char *str);
char *my_strcpy(char const *src);
char *my_strncpy(char const *src, int len);
char *my_strcat(char *dest, char const *src);
int my_end(char const *sbuff);
char *get_current_line(int fd, char *sbuff, int size, int *sizemax);
char *get_next_line(int fd);
char **my_tabcpy(char **src);
char **my_tabcat(char **src, char const *str);
char **my_str_to_pathlist(char const *paths);
char *my_get_in_env(char const *key, char **env);
char **my_getpath_in_env(char **env);
char *my_give_target(int argc, char **argv, char **env, char const *last);
void my_cd(int argc, char **argv, char **env);
int my_str_isalphanum(char const *str);
int my_setenv_err(int argc, char **argv, char **env);
char **my_setenv(int argc, char **argv, char **env);
char **my_unsetenv(int argc, char **argv, char **env);
int my_check_path(char const *buff, char const *arg);
int check_err(int Child_status);
int my_exec(char **prog_av, int len, char **env);
int my_is_keystr(char const *str);
char **my_chose_function(char **argv, char **env);
int waiting_input(char **env);
#endif