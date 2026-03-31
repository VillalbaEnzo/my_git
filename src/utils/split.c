/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell2-7 [WSL: Ubuntu-24.04]
** File description:
** split.c
*/

#include "my.h"

static char **fill_token(char **buf, char *str_copy, char *delimiter)
{
    char *save_ptr = NULL;
    char *token = strtok_r(str_copy, delimiter, &save_ptr);
    int i = 0;

    while (token != NULL) {
        buf[i] = my_strdup(token);
        if (!buf[i]) {
            buf[i] = NULL;
            free_double_buf(buf);
            free(str_copy);
            return NULL;
        }
        i++;
        token = strtok_r(NULL, delimiter, &save_ptr);
    }
    buf[i] = NULL;
    free(str_copy);
    return buf;
}

char **split(char *str, char *delimiter)
{
    char **buf = NULL;
    char *str_copy = my_strdup(str);

    if (!str_copy)
        return NULL;
    buf = malloc(sizeof(char *) * (my_strlen(str) + 1));
    if (!buf) {
        free(str_copy);
        return NULL;
    }
    return fill_token(buf, str_copy, delimiter);
}
