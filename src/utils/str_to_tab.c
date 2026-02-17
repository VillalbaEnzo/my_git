/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-bsminishell1-6
** File description:
** str_to_tab.c
*/

#include "my.h"

static char *newline_clear(char *str)
{
    int i = 0;

    if (!str)
        return NULL;
    while (str[i] != '\n' && str[i] != '\0')
        i++;
    if (str[i] == '\n')
        str[i] = '\0';
    return str;
}

char **str_to_tab(char *str)
{
    char **buf = NULL;
    int i = 0;
    char *token = NULL;

    if (!str)
        return NULL;
    str = newline_clear(str);
    buf = malloc(sizeof(char *) * (my_strlen(str) + 1));
    if (!buf)
        return NULL;
    token = strtok(str, " ");
    while (token != NULL) {
        buf[i] = my_strdup(token);
        if (!buf[i])
            return NULL;
        i++;
        token = strtok(NULL, " ");
    }
    buf[i] = NULL;
    return buf;
}
