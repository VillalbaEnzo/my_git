/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell2-7 [WSL: Ubuntu-24.04]
** File description:
** add_spaces_redir.c
*/

#include "my.h"

static int count_chevrons(char *str)
{
    int count = 0;

    if (!str)
        return 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == '<' || str[i] == '>')
            count++;
    }
    return count;
}

static int handle_chevron(char *new_str, char *str, int *i, int j)
{
    new_str[j] = ' ';
    j++;
    new_str[j] = str[*i];
    j++;
    if (str[*i + 1] == str[*i]) {
        new_str[j] = str[*i + 1];
        j++;
        (*i)++;
    }
    new_str[j] = ' ';
    j++;
    return j;
}

static char *add_spaces(char *str, char *new_str)
{
    int i = 0;
    int j = 0;

    if (!str || !new_str)
        return NULL;
    while (str[i]) {
        if (str[i] == '<' || str[i] == '>')
            j = handle_chevron(new_str, str, &i, j);
        else {
            new_str[j] = str[i];
            j++;
        }
        i++;
    }
    new_str[j] = '\0';
    return new_str;
}

char *handle_add_spaces(char *str)
{
    int len = 0;
    char *new_str = NULL;

    if (!str)
        return NULL;
    len = my_strlen(str) + (count_chevrons(str) * 2) + 1;
    new_str = malloc(sizeof(char) * len);
    if (!new_str)
        return NULL;
    return add_spaces(str, new_str);
}
