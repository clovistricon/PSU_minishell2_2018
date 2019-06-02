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
int my_strcomp(char const *str1, char const *str2);
void free_tab(char **tab);
int my_str_is_empty(char const *str);
int my_str_isalphanum(char const *str);
char *my_strcpy(char const *src);
char *my_strncpy(char const *src, int len);
char *my_str_replace(char *dest, char *src);
char *my_strcat(char const *dest, char const *src);
char **my_tabcpy(char **src);
char **my_tabcat(char **src, char const *str);
char **my_tabcat_replace(char **src, char *str);
char *get_current_line(int fd, char *sbuff, int *sizemax);
char *get_next_line(int fd);
int check_err(int Child_status);
int my_str_err(int err);
char **my_str_to_word_array(char const *str);
char **my_str_to_cmd_arr(char *str);
int my_end(char const *sbuff);
char **my_str_to_pathlist(char const *paths);
char *my_get_in_env(char const *key, char **env);
char **my_getpath_in_env(char **env);
char *my_give_target(int argc, char **argv, char **env, char const *last);
void my_cd(int argc, char **argv, char **env);
int my_setenv_err(int argc, char **argv, char **env);
char **my_setenv(int argc, char **argv, char **env);
char **my_unsetenv(int argc, char **argv, char **env);
char *my_check_path(char const *arg, char **path);
void reset_fd(int p[2]);
int my_get_argc(char **av);
int my_is_keystr(char const *str);
int my_exec(char **prog_av, char **env, int p[2]);
int my_put_out(char const *direc, char const *file);
int get_keyboard(char const *str);
int my_put_in(char const *direc, char const *file);
int my_redirections(char const *direction, char const *arg);
int my_pipe(char **prog_av, char ***env, int p[2]);
int check_pipe(char **av, int j, int entry, int in);
char **my_chose_function(char **argv, char **env, int p[2]);
int my_exec2(char **prog_av, char ***env);
int my_exec_pipe(char *cmd, char ***env);
int my_exec_for(char const *cmdline, char ***env);
int waiting_input(char **env);
#endif