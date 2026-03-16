/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell2-7 [WSL: Ubuntu-24.04]
** File description:
** trim.c
*/

#include "my.h"

char *trim(char *str)
{
    char *new_str = NULL;
    int first = 0;
    int last = 0;

    if (!str)
        return NULL;
    while (str[first] == ' ' || str[first] == '\t')
        first++;
    if (str[first] == '\0')
        return NULL;
    last = my_strlen(str) - 1;
    while (last > first && (str[last] == ' ' || str[last] == '\t'))
        last--;
    new_str = malloc(sizeof(char) * (last - first + 2));
    if (!new_str)
        return NULL;
    my_strncpy(new_str, str + first, last - first + 1);
    new_str[last - first + 1] = '\0';
    return new_str;
}
