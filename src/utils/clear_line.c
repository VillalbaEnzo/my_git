/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** clear_line.c
*/

#include "my.h"

static char *space_clear(char *str)
{
    int i = 0;
    int j = 0;
    int end = my_strlen(str) - 1;

    if (!str)
        return NULL;
    while (str[i] == ' ')
        i++;
    while (end >= i && str[end] == ' ')
        end--;
    while (i <= end) {
        str[j] = str[i];
        j++;
        i++;
    }
    if (str[my_strlen(str) - 1] == '\n')
        str[my_strlen(str) - 1] = '\0';
    return str;
}

static char *newline_clear(char *str)
{
    int i = 0;

    if (!str)
        return NULL;
    while (str[i] != '\n')
        i++;
    str[i] = '\0';
    return str;
}

char *clear_line(char *str)
{
    if (!str)
        return NULL;
    str = newline_clear(str);
    if (!str)
        return NULL;
    str = space_clear(str);
    if (!str)
        return NULL;
    return str;
}
