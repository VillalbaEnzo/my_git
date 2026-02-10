/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
** File description:
** print_padding
*/

#include "../include/my.h"

void print_padding(char c, int n, int *count)
{
    for (int i = 0; i < n; i++)
        *count += my_putchar(c);
}
