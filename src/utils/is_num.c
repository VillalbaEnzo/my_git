/*
** EPITECH PROJECT, 2025
** next
** File description:
** main.c
*/

#include "my.h"

int is_num(char c)
{
    if (c < '0' || c > '9')
        return 0;
    return 1;
}

int is_num_from_str(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (!is_num(str[i]) && str[i] != '-')
            return 0;
    }
    return 1;
}
