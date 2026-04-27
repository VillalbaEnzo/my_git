/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-42sh-2 [WSL: Ubuntu-24.04]
** File description:
** is_numeric.c
*/

#include "utils.h"
#include "mysh.h"

bool is_numeric(char *str)
{
    if (!str || !(*str))
        return false;
    if (*str == '-' || *str == '+')
        str++;
    if (!(*str))
        return false;
    for (int i = 0; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}
