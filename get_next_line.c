/*
** EPITECH PROJECT, 2018
** get_next_line
** File description:
** read line in file descriptor
*/
#include "my.h"

char *my_strcpy(char const *src)
{
    int a = 0;
    int len;
    char *dest;

    if (src == NULL)
        return (NULL);
    for (len = 0; src[len] != '\0'; len = len + 1);
    dest = malloc(sizeof(char) * (len + 1));
    while (src[a] != '\0') {
        dest[a] = src[a];
        a = a + 1;
    }
    dest[a] = '\0';
    return (dest);
}

char *my_strcat(char const *dest, char const *src)
{
    int len1 = 0;
    int len2 = 0;
    char *fuse;
    int a = 0;

    if (dest == NULL) {
        fuse = my_strcpy(src);
        return (fuse);
    }
    for (len1 = 0; dest[len1] != '\0'; len1 = len1 + 1);
    for (len2 = 0; src[len2] != '\0'; len2 = len2 + 1);
    fuse = malloc(sizeof(char) * (len1 + len2 + 1));
    for (; dest[a] != '\0'; a = a + 1)
        fuse[a] = dest[a];
    for (int b = 0; src[b] != '\0'; b = b + 1) {
        fuse[a] = src[b];
        a = a + 1;
    }
    fuse[a] = '\0';
    return (fuse);
}

int my_end(char const *sbuff)
{
    if (sbuff == NULL)
        return (0);
    for (int i = 0; sbuff[i] != '\0'; i = i + 1) {
        if (sbuff[i] == '\n')
            return (i);
    }
    return (0);
}

char *get_current_line(int fd, char *sbuff, int *sizemax)
{
    int size;
    char *buff;

    while (my_end(sbuff) == 0) {
        if ((sbuff != NULL) && (sbuff[0] == '\n'))
            break;
        buff = malloc(sizeof(char) * (READ_SIZE + 1));
        size = read(fd, buff, READ_SIZE);
        if (size <= 0) {
            free(buff);
            break;
        }
        buff[size] = '\0';
        sbuff = my_strcat(sbuff, buff);
        free(buff);
    }
    if (sbuff != NULL)
        for (; sbuff[*sizemax] != '\0'; *sizemax = *sizemax + 1);
    return (sbuff);
}

char *get_next_line(int fd)
{
    static char *buff = NULL;
    char *sbuff = NULL;
    int sizemax = 0;
    int size;

    if (fd < 0)
        return (NULL);
    if (buff != NULL) {
        sbuff = my_strcpy(buff);
        free(buff);
    }
    sbuff = get_current_line(fd, sbuff, &sizemax);
    if (sizemax == 0)
        return (NULL);
    else if ((size = my_end(sbuff)) < sizemax) {
        buff = my_strcpy(&sbuff[size + 1]);
        sbuff[my_end(sbuff)] = '\0';
    }
    return (sbuff);
}