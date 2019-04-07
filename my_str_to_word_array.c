/*
** EPITECH PROJECT, 2018
** str_to_word_array
** File description:
** sépart string en tab de mots
*/
#include "my.h"

char *my_str_replace(char *dest, char *src)
{
    char *str = my_strcpy(src);

    free(dest);
    return (str);
}

char **my_str_to_word_array(char const *str)
{
    char **word_arr = NULL;
    char *word;
    int i = 0;
    int i0 = 0;

    if ((str == NULL) || (*str == 0))
        return (NULL);
    while (str[i] != '\0') {
        for (; (str[i] != '\0') && ((str[i] < 33) || (str[i] > 126)); i++);
        if (str[i] == '\0')
            break;
        i0 = i;
        for (; (str[i] > 32) && (str[i] < 127); i++);
        word = my_strncpy(&str[i0], (i - i0));
        word_arr = my_tabcat(word_arr, word);
        free(word);
    }
    return (word_arr);
}