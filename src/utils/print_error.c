/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell2-7 [WSL: Ubuntu-24.04]
** File description:
** print_error.c
*/

#include "my.h"

int print_error(char *msg, int len)
{
    write(2, msg, len);
    return 0;
}
