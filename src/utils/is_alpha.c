/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell2-7 [WSL: Ubuntu-24.04]
** File description:
** is_alpha.c
*/

#include "my.h"

int is_alpha(char *str, char c)
{
    if (!str)
        return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
    for (int i = 0; str[i]; i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
                (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'))
            return 0;
    }
    return 1;
}
