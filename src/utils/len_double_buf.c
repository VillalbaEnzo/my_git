/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell2-7 [WSL: Ubuntu-24.04]
** File description:
** len_double_buf.c
*/

#include "my.h"

int len_double_buf(char **buf)
{
    int len = 0;

    if (!buf)
        return 0;
    while (buf[len])
        len++;
    return len;
}
