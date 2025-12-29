/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** my_top.c
*/

#include "my.h"

void print_helper(void)
{
    my_putstr("Usage: my_top [options]\n");
    my_putstr("Options:\n");
    my_putstr("  -h          Display this help\n");
    my_putstr("  -U <user>   Filter by user\n");
    my_putstr("  -n <num>    Number of frames\n");
    my_putstr("  -s <sec>    Refresh delay in seconds\n");
}
