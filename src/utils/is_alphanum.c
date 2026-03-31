/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell2-7 [WSL: Ubuntu-24.04]
** File description:
** is_alphanum.c
*/

#include "my.h"

int is_alphanum(char *str, char c)
{
    if (!str)
        return (is_alpha(NULL, c) || (c >= '0' && c <= '9'));
    for (int i = 0; str[i]; i++) {
        if (!(is_alpha(NULL, str[i]) ||
                (str[i] >= '0' && str[i] <= '9')))
            return 0;
    }
    return 1;
}
